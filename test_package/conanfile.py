import os
from conans import ConanFile, AutoToolsBuildEnvironment, tools

class ThorsSerializerTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "ThorsSerializer/2.2.18@user/testing"

    def build(self):
        with tools.chdir(self.source_folder):
            self.run("pwd")
            self.run("ls")
            atools = AutoToolsBuildEnvironment(self)
            atools.make(target = "ThorsSerializerTest")

    def test(self):
        self.run(["%s%sThorsSerializerTest" % (self.source_folder, os.sep)], run_environment=True)

