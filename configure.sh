if ! command -v openssl version &> /dev/null
then
    echo "Openssl could not be found, please install it"
else
    echo "Openssl installed"
fi

if [[ $(ldconfig -p | grep flint-2.5.2) ]]; then
    echo "flint-2.5.2 installed"
else
    echo "flint-2.5.2 not installed, please install it"
fi

if [[ $(ldconfig -p | grep gmp) ]]; then
    echo "GMP installed"
else
    echo "GMP not installed, please install it"
fi
