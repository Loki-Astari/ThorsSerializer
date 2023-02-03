from conans import ConanFile, AutoToolsBuildEnvironment
from conans import tools

class ThorsSerializerTestConan(ConanFile):
    name = "ThorsSerializerTest"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "ThorsSerializer/2.2.18@user/testing"

    def build(self):
        self.run("pwd")
        self.run("ls")
        with tools.chdir("test_package"):
            self.run("pwd")
            self.run("ls")
            atools = AutoToolsBuildEnvironment(self)
            atools.make()

    def package(self):
        self.copy("ThorsSerializerTest17", dst="bin",     src="../build/bin")

    def package_info(self):
        self.copy("*", src="bin",     dst="bin")
