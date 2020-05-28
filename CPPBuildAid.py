import sys
import argparse
import subprocess
import shutil
import os
import glob
from datetime import datetime


def generateSourceList():
    sourceFileLines = 0

    sourceFiles = []
    sourcePath = os.path.join(os.getcwd(), "src")
    if (sourcePath):
        for dirpath, dirs, files in os.walk(sourcePath):
            for filename in files:
                if(str(filename).endswith('.c') or str(filename).endswith('.cpp')):
                    relativeFilePath = os.path.relpath(os.path.join(dirpath, filename), os.getcwd())
                    sourceFiles.append(relativeFilePath)

                    # Counting source code lines
                    if("lib" not in dirpath and "library" not in dirpath):
                        with open(os.path.join(dirpath, filename), "r") as sourcefile:
                            sourceFileLines += len(sourcefile.readlines())
        print("Total source code lines: {}".format(sourceFileLines))
        return sourceFiles
    else:
        print("Unable to find src directory. Terminating")
        exit(1)


def generateIncludeList():
    headerFileLines = 0

    headerFileDirectories = []
    includePath = os.path.join(os.getcwd(), "include")
    if (includePath):
        for dirpath, dirs, files in os.walk(includePath):
            relativeDirectoryPath = os.path.relpath(dirpath, os.getcwd())
            headerFileDirectories.append(relativeDirectoryPath)

            # Counting headerfile lines of code
            if("lib" not in dirpath and "library" not in dirpath):
                for filename in files:
                    if(str(filename).endswith('.h') or str(filename).endswith('.hpp')):
                        with open(os.path.join(dirpath, filename), "r") as headerfile:
                            headerFileLines += len(headerfile.readlines())
        print("Total header code lines: {}".format(headerFileLines))
        return headerFileDirectories
    else:
        print("Unable to find include directory. Terminating")
        exit(1)


def build(argv):
    print("Starting CPPBuildAid")
    startTime = datetime.now()

    argumentParser = argparse.ArgumentParser()
    argumentParser.add_argument("-bt", "--buildType")
    argumentParser.add_argument("-t", "--threads")

    args = argumentParser.parse_args()

    typeOfBuild = "debug"
    if(args.buildType == "release"):
        typeOfBuild = "release"

    threads = 1
    if(args.threads is not None and int(args.threads) >= 1):
        threads = args.threads

    relativeSourceFilePaths = generateSourceList()
    sourceListFile = open("sourcelist.cmake", "w")
    for relativeSourceFilePath in relativeSourceFilePaths:
        sourceListFile.write(relativeSourceFilePath + "\n")
    sourceListFile.close()

    relativeHeaderFileDirectories = generateIncludeList()
    includeListFile = open("includelist.cmake", "w")
    for relativeHeaderFileDirectory in relativeHeaderFileDirectories:
        includeListFile.write(relativeHeaderFileDirectory + "\n")
    includeListFile.close()

    print("Running cmake")
    print("Using {} threads to build in {}-mode".format(threads, typeOfBuild))

    subprocess.call(["cmake", "-S.", "-Bbuild"])
    resultBuildType = subprocess.call(["cmake", "-DCMAKE_BUILD_TYPE={}".format(typeOfBuild.capitalize()), "."], cwd="build")
    resultBuild = subprocess.call(["cmake", "--build", ".", "-j", str(threads)], cwd="build")

    if(resultBuildType != 0 or resultBuild != 0):
        print("Build failed with errors")
        exit(1)
    print("Build completed successfully in {} ms.".format(datetime.now() - startTime))


def main():
    build(sys.argv)


if __name__ == "__main__":
    main()