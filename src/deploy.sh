#!/bin/bash 

scp /home/gitlab-runner/builds/kQGNUgsN/0/students_repo/etsyhone/DO6_CICD.ID_356283-1/src/cat/s21_cat diana@192.168.0.2:/usr/local/bin

scp /home/gitlab-runner/builds/kQGNUgsN/0/students_repo/etsyhone/DO6_CICD.ID_356283-1/src/grep/s21_grep diana@192.168.0.2:/usr/local/bin

ssh diana@192.168.0.2 ls /usr/local/bin
