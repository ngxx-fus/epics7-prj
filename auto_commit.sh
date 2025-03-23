#! /bin/sh

w_color='\e[93m'
e_color='\e[91m'
color='\e[94m'
norm='\e[0m'

params=$#

message="changed"
branch_name="multiple-sensors"

__check_nextparam() {
    # only accept TWO parametter; 1st param is the option and 2nd param is value!
    option=$1
    next_param=$2
    error_flag=0
    # check zero (empty)
    if [ -z "$next_param" ]; then 
        #    >&2    : send output as error (stderr)
        printf "${e_color}\`$option\` requires a value!${norm}\n" >&2
        error_flag=1
    # check option
    else 
        case "$next_param" in
            --*)
                printf "${e_color}\`$option\` requires a value, not an option!${norm}\n" >&2
                error_flag=1
                ;;
        esac
    fi

    # printf "Check done: error_flag = $error_flag"

    if [ $error_flag -eq 1 ]; then
        return 1
    else
        return 0
    fi
}

skip_flag=0

for i in  $(seq 1 $params); do
    # evaluate ith param 
    eval "param=\$$i"
    printf "param[$i] = $param\n"
    case $param in
        --message)
            # evaluate next_param
            eval "next_param=\$$((i+1))"
            # check next param
            __check_nextparam $param $next_param
            # 
            # if there's no error, then assign the value
            if [ $? -eq 0 ]; then
                # assign message
                message="$($next_param)"
                skip_flag=1
                continue
            else
                printf "${w_color}\`$param\` is skipped; use default value (\"$message\")!${norm}\n"
                continue
            fi
            ;;
        --branch)
            # evaluate next_param
            eval "next_param=\$$((i+1))"
            # check next param
            __check_nextparam $param $next_param
            # if there's no error, then assign the value
            if [ $? -eq 0 ]; then
                # assign branch name
                branch_name="$next_param"
                skip_flag=1
                shift 2
                continue
            else
                printf "${w_color}\`$param\` is skipped; use default value (\"$branch_name\")!${norm}\n"
                continue
            fi
            ;;
        *)
            if [ $skip_flag -eq 1 ]; then
                skip_flag=0
                continue; 
            fi
            echo "${e_color}Unknown option: $param${norm}" >&2
            ;;
    esac
done


printf "${color}git add -A${norm}\n"
# git add -A

printf "${color}git commit -m \"$(date +"%R %d/%m") - $message\"${norm}\n"
# git commit -m "$(date + "%R %d/%m") - $message"

printf "${color}git push -u $branch_name${norm}\n"
# git push -u single-sensor