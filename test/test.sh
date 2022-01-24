#!/bin/bash

################ VARIABLES GLOBALES ################

GREEN="\033[38;5;113m"
RED="\033[38;5;160m"
GREY="\033[38;5;109m"
ORANGE="\033[38;5;208m"
WHITE="\033[38;5;15m"
CYAN="\033[38;5;51m"
PURPLE="\033[38;5;135m"
RESET="\033[0m"

################ MAKE ################

cd ..
make

################ FUNCTIONS ################

test_hash ()
{
    echo -e "$RED################################################"
    if [[ "$1" == "md5" ]]
    then
        echo -e "##############    MD5 ALGORITHM    #############"
    elif [[ "$1" == "sha256" ]]
    then
        echo -e "############    SHA256 ALGORITHM    ############"
    elif [[ "$1" == "base64" ]]
    then
        echo -e "############    BASE64 ALGORITHM    ############"
    elif [[ "$1" == "des-ecb" ]]
    then
        echo -e "###########    DES-ECB ALGORITHM    ############"
    elif [[ "$1" == "des-cbc" ]]
    then
        echo -e "###########    DES-CBC ALGORITHM    ############"
    fi
    echo -e "################################################$RESET\n"

    echo -e "$ORANGE################################################"
    echo -e "#######    TEST MULTIPLE STDIN INPUTS    #######"
    echo -e "################################################$RESET\n"
    for nb_bytes in {0..2048}
    do
        let "step = $nb_bytes % 100"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 2048"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_RESULT=$(cat file | openssl $1 | awk '{print $2}')
        CUSTOM_SSL_RESULT=$(cat file | ./ft_ssl $1 -q)
        if [[ "$OPENSSL_RESULT" != "$CUSTOM_SSL_RESULT" ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON TEST $nb_bytes"
            echo -e "$RESET"
            break
        fi
    done
    echo "2048 / 2048"
    echo ""
}

test_base64 ()
{
    echo -e "$RED################################################"
    echo -e "############    BASE64 ALGORITHM    ############"
    echo -e "################################################$RESET\n"

    for nb_bytes in {0..2048}
    do
        let "step = $nb_bytes % 100"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 2048"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_ENCODE=$(cat file | base64 > base64_encode.txt)
        CUSTOM_SSL_ENCODE=$(cat file | ./ft_ssl base64 -n > my_base64_encode.txt)
        DIFF_RESULT=$(diff base64_encode.txt my_base64_encode.txt)
        # echo $?
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON ENCODING $nb_bytes"
            echo -e "$RESET"
            break
        fi
        OPENSSL_DECODE=$(echo -n $OPENSSL_ENCODE | base64 -d > base64_decode.txt)
        CUSTOM_SSL_DECODE=$(echo -n $CUSTOM_SSL_ENCODE | ./ft_ssl base64 -d > my_base64_decode.txt)
        DIFF_RESULT=$(diff base64_decode.txt my_base64_decode.txt)
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON DECODING $nb_bytes"
            echo -e "$RESET"
            echo -e "$CUSTOM_SSL_ENCODE"
            break
        fi
    done
    echo "2048 / 2048"
    echo ""
}

test_des()
{
    echo -e "$RED################################################"
    echo -e "############    DES-ECB ALGORITHM    ###########"
    echo -e "################################################$RESET\n"

    for nb_bytes in {0..2048}
    do
        let "step = $nb_bytes % 100"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 2048"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_ENCRYPT=$(cat file | openssl des-ecb -e -K "AAAABBBBCCCCDDDD" -out des_encrypt.txt)
        CUSTOM_SSL_ENCRYPT=$(cat file | ./ft_ssl des-ecb -e -k "AAAABBBBCCCCDDDD" -o my_des_encrypt.txt)
        DIFF_RESULT=$(diff des_encrypt.txt my_des_encrypt.txt)
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON ENCRYPTION $nb_bytes"
            echo -e "$RESET"
            break
        fi
        OPENSSL_DECRYPT=$(cat des_encrypt.txt | openssl des-ecb -d -K "AAAABBBBCCCCDDDD" -out des_decrypt.txt)
        CUSTOM_SSL_DECRYPT=$(cat my_des_encrypt.txt | ./ft_ssl des-ecb -d -k "AAAABBBBCCCCDDDD" -o my_des_decrypt.txt)
        DIFF_RESULT=$(diff des_decrypt.txt my_des_decrypt.txt)
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON DECRYPTION $nb_bytes"
            echo -e "$RESET"
            echo -e "$CUSTOM_SSL_ENCODE"
            break
        fi
    done
    echo "2048 / 2048"
    echo ""


    echo -e "$RED################################################"
    echo -e "############    DES-CBC ALGORITHM    ###########"
    echo -e "################################################$RESET\n"

    for nb_bytes in {0..2048}
    do
        let "step = $nb_bytes % 100"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 2048"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_ENCRYPT=$(cat file | openssl des-cbc -e -K "AAAABBBBCCCCDDDD" -iv "AAAABBBBCCCCDDDD" -out des_encrypt.txt)
        CUSTOM_SSL_ENCRYPT=$(cat file | ./ft_ssl des-cbc -e -k "AAAABBBBCCCCDDDD" -v "AAAABBBBCCCCDDDD" -o my_des_encrypt.txt)
        DIFF_RESULT=$(diff des_encrypt.txt my_des_encrypt.txt)
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON ENCRYPTION $nb_bytes"
            echo -e "$RESET"
            break
        fi
        OPENSSL_DECRYPT=$(cat des_encrypt.txt | openssl des-cbc -d -K "AAAABBBBCCCCDDDD" -iv "AAAABBBBCCCCDDDD" -out des_decrypt.txt)
        CUSTOM_SSL_DECRYPT=$(cat my_des_encrypt.txt | ./ft_ssl des-cbc -d -k "AAAABBBBCCCCDDDD" -v "AAAABBBBCCCCDDDD" -o my_des_decrypt.txt)
        DIFF_RESULT=$(diff des_decrypt.txt my_des_decrypt.txt)
        if [[ $? != 0 ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON DECRYPTION $nb_bytes"
            echo -e "$RESET"
            echo -e "$CUSTOM_SSL_ENCODE"
            break
        fi
    done
    echo "2048 / 2048"
    echo ""
}
#test_hash "md5"
#test_hash "sha256"
# test_base64
test_des

################ CLEAN ################

echo ""
# make fclean
# rm file
# 14 octects
# 4 pleins
# padding de 8 bits
# 