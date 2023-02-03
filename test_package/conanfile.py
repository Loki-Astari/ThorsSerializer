import os
from conans import ConanFile, AutoToolsBuildEnvironment, tools

class ThorsSerializerTestConan(ConanFile):
    settings = "cppstd", "os", "compiler", "build_type", "arch"
    requires = "ThorsSerializer/2.2.18@user/testing"
    cppminimum = 17

    def configure(self):
        if not self.settings.cppstd:
            self.settings.cppstd = self.cppminimum

    def build(self):
        with tools.chdir(self.source_folder):
            atools = AutoToolsBuildEnvironment(self)
            atools.make(target = "ThorsSerializerTest")

    def test(self):
        self.run(["%s%sThorsSerializerTest" % (self.source_folder, os.sep)], run_environment=True)

