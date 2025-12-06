#!/bin/bash

###################################################################
#Script Name	: checkpoint.sh
#Description	: This script is used to test Checkpoint 2
#Args           : -i <path-to-code-folder> -o <path-to-results-folder>
#Author       	: ASCN Team
###################################################################

SRC_FOLDER=$(pwd)/codebase
VAULT_PASS="ascn2526"

################################
# Log message to file(s)       #
################################
function log_msg {
    MSG="$1"
    LOG_FILE="$2"

    echo -e -n "$MSG" >> "$LOG_FILE"

    if [ -n "$3" ]
    then
        echo -e "$MSG" >> "$3"
    fi

}

################################
# Setup the environment        #
################################
function setup {
    echo "> Setting up"
    LOGS=$1
    mkdir -p $LOGS

    # prepare_tests
    clean_up
}


################################
# Cleaning up                  #
################################
function clean_up {
    echo "> Cleaning resources..."
    kubectl get namespaces --no-headers | \
        grep -vE '^(default|kube-system|kube-public|gke-system|gke-managed-cim|gmp-system|gmp-public|kube-node-lease|gke-managed-system)' | \
        awk '{print $1}' | \
        xargs -I {} kubectl delete namespace {}
    kubectl delete all --all --namespace=default > /dev/null 2>&1
    kubectl delete pvc --all -A > /dev/null 2>&1
    kubectl delete sc --all --namespace=default > /dev/null 2>&1
}

################################
# Check directory structure    #
################################
function check_structure {
    echo "> Checking directory structure..."
    TEST_PATH="$1"
    LOGS="$2"
    CHECK=$3
    LOG_FILE="$LOGS/checkpoint$CHECK.log"
    TASK_LOG="$LOGS/task-1.log"


    cd $TEST_PATH > /dev/null 2>&1

    log_msg "[Task-1] Checking directory structure..." "$LOG_FILE" "$TASK_LOG"
    missingFiles=false

    ansible_structure=("inventory/gcp.yml" "roles")
    required_playbooks=("gke-cluster-create.yml" "gke-cluster-destroy.yml" "airtrail-deploy.yml" "airtrail-undeploy.yml" "test-all.yml")

    for file in "${ansible_structure[@]}"
    do
        if [ -e $file ]
        then
            continue
        else
            echo -e "\t[Task-1] $file does not exist" >> "$TASK_LOG" 2>&1
            missingFiles=true
        fi
    done

    for playbook in "${required_playbooks[@]}"
    do
        if [ -e $playbook ]
        then
            continue
        else
            echo -e "\t[Task-1] $playbook does not exist" >> "$TASK_LOG" 2>&1
            missingFiles=true
        fi
    done

    if [ $missingFiles = true ]
    then
        echo -e "FAILED!"
        echo "[Task-1] Failed! Missing the required files!" >> "$TASK_LOG" 2>&1
        echo -e "FAILED! Check task-1.log for more information."  >> "$LOG_FILE" 2>&1
        failedRepoStructure+=("$1")
        return 1
    else
        echo -e " OK!" >> "$LOG_FILE" 2>&1
        echo "[Task-1] OK! Directory structure is correct!" >> "$TASK_LOG" 2>&1
    fi
    return 0
}

################################
# Prepare Tests Setup          #
################################
function prepare_tests {
    echo "> Preparing tests setup..."
    TEST_PATH="$1"
    LOGS="$2"
    CHECK=$3
    LOG_FILE="$LOGS/checkpoint$CHECK.log"
    TASK_LOG="$LOGS/task-1.log"
    cd $1 > /dev/null 2>&1

    log_msg "[Task-1] Preparing tests setup..." "$LOG_FILE" "$TASK_LOG"
    cp -r $SRC_FOLDER/roles/test_airtrail roles/  >> "$TASK_LOG" 2>&1
    if [ $? -ne 0 ]
    then
        echo -e "FAILED!" >> "$TASK_LOG" 2>&1
        return 1
    fi
    cp $SRC_FOLDER/test-all.yml .  >> "$TASK_LOG" 2>&1
    if [ $? -ne 0 ]
    then
        echo "[Task-1] Setup FAILED!" >> "$TASK_LOG" 2>&1
        return 1
    fi
    echo -e -n "$VAULT_PASS" > .vault_pass
    echo "[Task-1] Setup OK!" >> "$TASK_LOG" 2>&1
    return 0
}

#####################################
# Test                              #
# --------------------------------- #
# $1: test number                   #
# $2: code folder                   #
# $3: logs folder                   #
# $4: extra args                    #
#####################################
function run_test_n {
    echo "> Running Test $1..."
    TEST_PATH="$2"
    LOGS="$3"
    CHECK="$4"
    LOG_FILE="$LOGS/checkpoint$CHECK.log"
    TASK_LOG="$LOGS/task-$1.log"
    EXTRA_ARGS="$5"


    # Enter Code directory
    cd $TEST_PATH > /dev/null 2>&1

    skip_tags=""
    if [ $1 -eq 1 ]
    then
        skip_tags="--skip-tags test2,test3,test4,test5"
    elif [ $1 -eq 2 ]
    then
        skip_tags="--skip-tags test1,test3,test4,test5"
    elif [ $1 -eq 3 ]
    then
        skip_tags="--skip-tags test1,test2,test4,test5"
    elif [ $1 -eq 4 ]
    then
        skip_tags="--skip-tags test1,test2,test3,test5"
    elif [ $1 -eq 5 ]
    then
        skip_tags="--skip-tags test1,test2,test3,test4"
    fi

    # Run Test 1
    log_msg "[Task-$1] Starting test $1" "$LOG_FILE" "$TASK_LOG"
    ansible-playbook -i inventory/gcp.yml test-all.yml $skip_tags --vault-password-file .vault_pass $EXTRA_ARGS -e 'ansible_python_interpreter=/home/vagrant/.checkpoints/bin/python3' >> "$TASK_LOG" 2>&1
    if [ $? -eq 0 ]
    then
        echo -e " OK!"  >> "$LOG_FILE" 2>&1
    else
        echo -e " FAILED! Check task-$1.log for more information."  >> "$LOG_FILE" 2>&1
        return 1
    fi

    return 0
}

################################
# Main function                #
################################
function main {
    echo "Running Checkpoint $3 for \"$1\""
    CUR_PATH=$(pwd)

    case $2 in
        /*) LOGS_FOLDER=$2 ;;
        *) LOGS_FOLDER="$CUR_PATH/$2" ;;
    esac

    CHECK=$3
    EXTRA_ARGS=$4

    if [ $CHECK -eq 2 ]
    then
        MAX=3
    else
        MAX=5
    fi

    echo "Logs will be saved in \"$LOGS_FOLDER\""
    setup "$LOGS_FOLDER"

    check_structure "$1" "$LOGS_FOLDER" "$CHECK"
    if [ $? -ne 0 ]
    then
        clean_up
        echo "Test 0 failed! Check $LOGS_FOLDER/checkpoint$CHECK.log for more information."
        return 1
    fi

    # Prepare tests
    prepare_tests "$1" "$LOGS_FOLDER" "$CHECK"
    if [ $? -ne 0 ]
    then
        clean_up
        echo "Test 0 failed! Check $LOGS_FOLDER/checkpoint$CHECK.log for more information."
        return 1
    fi

    # call run_test_n from 1 to MAX
    for i in $(seq 1 $MAX)
    do
        run_test_n $i "$1" "$LOGS_FOLDER" "$CHECK" "$EXTRA_ARGS"
        if [ $? -ne 0 ]
        then
            clean_up
            echo "Test $i failed! Check $LOGS_FOLDER/task-$i.log for more information."
            return $i
        fi
    done

    clean_up

    echo "Tests completed successfully! Check $LOGS_FOLDER/checkpoint$CHECK.log for more information."
    return 0
}


#########################
# The command line help #
#########################
display_help() {
    echo "Usage: $0 -i <path-to-code-folder> -o <path-to-results-folder>" >&2
    echo
    echo "   -i, --input           Code directory path to test"
    echo "   -o, --output          Output directory path to save logs"
    echo "   -c, --checkpoint      Choose which checkpoint to run (2 or 3)"
    echo "   -a, --arguments       Ansible extra arguments"
    echo
    exit 1
}

################################
# Check if parameters options  #
# are given on the commandline #
################################
input=""
output=""
while :
do
    case "$1" in
      -i | --input)
          if [ $# -ne 0 ]; then
            input="$2"
          fi
          shift 2
          ;;
      -o | --output)
          if [ $# -ne 0 ]; then
            output="$2"
          fi
          shift 2
          ;;
      -c | --checkpoint)
          if [ $# -ne 0 ]; then
            if [ $2 -eq 2 ] || [ $2 -eq 3 ]; then
                CHECK=$2
            else
                echo "Invalid checkpoint number. Please choose 2 or 3."
                exit 1
            fi
          fi
          shift 2
          ;;
      -a | --arguments)
          if [ $# -ne 0 ]; then
              EXTRA_ARGS="$2"
          fi
          shift 2
          ;;
      -h | --help)
          display_help
          exit 0
          ;;
      *)
          break
          ;;
    esac
done



################################
# Check if parameters are empty#
################################
if [ -z "$input" ] || [ -z "$output" ]; then
    display_help
    exit 1
fi

################################
# Call the main function       #
################################
main "$input" "$output" "$CHECK" "$EXTRA_ARGS"