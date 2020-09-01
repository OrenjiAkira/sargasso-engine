import os
from pathlib import Path

LIB_GLM_NAME = "glm"
LIB_GLM_SOURCE_PATH = str(
    Path(Path.cwd(), "third_party", LIB_GLM_NAME, LIB_GLM_NAME))
LIB_GLM_INSTALL_PATH = str(Path(Path.cwd(), "lib", LIB_GLM_NAME))
LIB_GLM_INCLUDE_PATH = str(Path(LIB_GLM_INSTALL_PATH, "include"))


def build() -> None:
    os.system("mkdir -p %s" % LIB_GLM_INCLUDE_PATH)
    copy_command = "cp -R %s %s" % (LIB_GLM_SOURCE_PATH, LIB_GLM_INCLUDE_PATH)
    if os.system(copy_command) != 0:
        raise Exception("GLM copy failed!")
