# ENCM 369 Winter 2026 Exercise E
# Program to generate data files for analysis by students.

import subprocess

def build_and_run(driver, options, source, executable):
    with open(executable + '_log.txt', 'w') as log: 
        print(f'building executable {executable}'
                + f' with command {driver} {options} {source} -o {executable}',
                  file=log)
        subprocess.run([driver, options, source, '-o', executable])

        for i in range(1, 11):
            print(f'\nrun #{i} of executable {executable} ...', file=log) 
            run_rv = subprocess.run(['./' + executable],
                                text=True,
                                capture_output=True)
            print(run_rv.stdout, file=log, end='')

build_and_run('clang', '', 'Array.c', 'ArrayPlain')
build_and_run('clang', '-O2', 'Array.c', 'ArrayO2')
build_and_run('clang', '-Os', 'Array.c', 'ArrayOs')
build_and_run('clang++', '', 'Set.cpp', 'SetPlain')
build_and_run('clang++', '-O2', 'Set.cpp', 'SetO2')
build_and_run('clang++', '-Os', 'Set.cpp', 'SetOs')
