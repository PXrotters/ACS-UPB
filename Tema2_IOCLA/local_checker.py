#!/usr/bin/env python3

import argparse
import subprocess
import shutil
import os
import sys
import re

#============================== ARGUMENTS ==============================#

argParser = argparse.ArgumentParser(description="Python Checker for PCLP2 Homework 2", prog="python3 checker.py")
group = argParser.add_mutually_exclusive_group()
group.add_argument("-t", "--task", help="Run tests for a certain task.")
group.add_argument("-b", "--bonus", action="store_true", help="Run tests for a the bonus task.")
group.add_argument("--all", action="store_true", help="Run all tasks.")
group.add_argument("--zip", action="store_true", help="Make zip file for VMChecker")
args = argParser.parse_args()

if len(sys.argv) == 1:
    argParser.print_help()
    exit(0)

#============================== CONSTANTS ==============================#

tasksNo = 4

runExec = "./"
checker = "checker"
taskDir = "task-"
bonusDir = "bonus/"

zipName = "VMChecker_Homework_2"

useShell = True

header = "======================= Tema 2 PCLP2 =======================\n"
#============================== FUNCTIONS ==============================#

def test_task(taskNo):
    global points

    taskString = f"{taskDir}{taskNo}/"
    procString = runExec + taskString + checker
    rc = subprocess.call(f"make -C {taskString} > /dev/null 2> /dev/null", shell=useShell)

    if rc != 0:
        sys.stderr.write("make failed with status %d\n" % rc)
        return

    if not os.path.exists(procString):
        sys.stderr.write("The file %s is missing and could not be created with \'make\'" % (taskString + checker))
        return

    checkerOutput = str(subprocess.check_output(f"cd {taskString} && ./checker", shell=useShell), encoding='utf-8')

    print(checkerOutput)
    taskScore = re.findall(r'\d+\.\d+', re.findall(fr'TASK {taskNo} SCORE: \d+\.\d+', checkerOutput)[0])[0]

    points += float(taskScore)

    rc = subprocess.call(f"make -C {taskString} clean > /dev/null 2> /dev/null", shell=useShell)

def test_bonus():
    global points
    
    procString = runExec + bonusDir + checker
    rc = subprocess.call(f"make -C {bonusDir} > /dev/null 2> /dev/null", shell=useShell)

    if rc != 0:
        sys.stderr.write("make failed with status %d\n" % rc)
        return

    if not os.path.exists(procString):
        sys.stderr.write("The file %s is missing and could not be created with \'make\'" % (bonusDir + checker))
        return

    checkerOutput = str(subprocess.check_output(f"cd {bonusDir} && ./checker", shell=useShell), encoding='utf-8')

    print(checkerOutput)
    taskScore = re.findall(r'\d+\.\d+', re.findall(fr'BONUS SCORE: \d+\.\d+', checkerOutput)[0])[0]

    points += float(taskScore)

    rc = subprocess.call(f"make -C {bonusDir} clean > /dev/null 2> /dev/null", shell=useShell)

#=======================================================================#

if args.zip:
    rc = subprocess.call(f"zip -r {zipName} */*.asm", shell=useShell)
    exit(rc)

print("\n" + header)

points = 10

#================================ TESTS ================================#

if args.task == None and args.all:
    for task in range(1, tasksNo + 1):
        test_task(task)
    test_bonus()
elif args.task != None:
    test_task(re.findall(r'\d', args.task)[0])
elif args.bonus:
    test_bonus()


print(f"====================== TOTAL {points} / 120 ======================\n")