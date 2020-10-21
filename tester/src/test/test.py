# ############################################################################ #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <charles.cabergs@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 21:48:50 by charles           #+#    #+#              #
#    Updated: 2020/09/11 17:00:25 by charles          ###   ########.fr        #
#                                                                              #
# ############################################################################ #

import os
import sys
import subprocess
import time

import config
from test.captured import Captured
from test.result import Result
import sandbox


class Test:
    def __init__(self,
                 cmd: str,
                 setup: str = "",
                 files: [str] = [],
                 exports: {str: str} = {},
                 timeout: float = config.TIMEOUT,
                 signal = None,
                 hook = None):
        self.cmd = cmd
        self.setup = setup
        self.files = files
        self.exports = exports
        self.result = None
        self.timeout = timeout
        self.signal = signal
        self.hook = hook

    def run(self):
        expected = self._run_sandboxed(config.REFERENCE_PATH, "-c")
        actual   = self._run_sandboxed(config.MINISHELL_PATH, "-c")
        s = self.cmd
        if self.setup != "":
            s = "[SETUP {}] {}".format(self.setup, s)
        if len(self.exports) != 0:
            s = "[EXPORTS {}] {}".format(
                    ' '.join(["{}='{:.20}'".format(k, v) for k, v in self.exports.items()]), s)
        self.result = Result(s, self.files, expected, actual)
        self.result.put()

    def _run_sandboxed(self, shell_path: str, shell_option: str) -> Captured:
        """ run the command in a sandbox environment

            capture the output (stdout and stderr)
            capture the content of the watched files after the command is run
        """

        sandbox.create()
        if self.setup != "":
            try:
                setup_status = subprocess.run(
                    self.setup,
                    shell=True,
                    cwd=config.SANDBOX_PATH,
                    stderr=subprocess.STDOUT,
                    stdout=subprocess.PIPE,
                    check=True
                )
            except subprocess.CalledProcessError as e:
                print("Error: `{}` setup command failed for `{}`\n\twith '{}'"
                      .format(self.setup,
                              self.cmd,
                              "no stderr" if e.stdout is None else e.stdout.decode().strip()))
                sys.exit(1)

        process = subprocess.Popen(
            [shell_path, shell_option, self.cmd],
            stderr=subprocess.STDOUT,
            stdout=subprocess.PIPE,
            cwd=config.SANDBOX_PATH,
            env={
                'PATH': config.PATH_VARIABLE,
                'TERM': 'xterm-256color',
                **self.exports,
            },
        )
        if self.signal is not None:
            time.sleep(0.2)
            process.send_signal(self.signal)
        else:
            try:
                process.wait(timeout=self.timeout)
            except subprocess.TimeoutExpired:
                return Captured.timeout()

        try:
            stdout, _ = process.communicate()
            output = stdout.decode()
        except UnicodeDecodeError:
            output = "UNICODE ERROR: {}".format(process.stdout)

        # capture watched files content
        files_content = []
        for file_name in self.files:
            try:
                with open(os.path.join(config.SANDBOX_PATH, file_name), "rb") as f:
                    files_content.append(f.read().decode())
            except FileNotFoundError as e:
                files_content.append(None)
        sandbox.remove()
        if self.hook is not None:
            output = self.hook(output)
        return Captured(output, process.returncode, files_content)
