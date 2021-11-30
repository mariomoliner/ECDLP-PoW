#include <stdio.h> 

int nextPrime(int x){
	int o;
	int k = x/6;
	int i = x - 6 * k;
	int aux;
	if(i<2){
		o = 1;
		aux = 4;
	}else{
		o = 5;
		aux = 2;
	}

	x = 6*k + o;
	printf("numero a encontrar el siguiente primo %d", x);


	for (;;x+=aux){
		if(aux == 4){
			aux =2;
		}
		else{
			aux = 4;
		}
		printf("%d\n",x);
		if(x>100){
			break;
		}
	}

}


int main(){
	nextPrime(12);

	return 0;
}


/*std::size_t
next_prime(std::size_t x)
{
    switch (x)
    {
    case 0:
    case 1:
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
    case 5:
        return 5;
    }
    std::size_t k = x / 6;
    std::size_t i = x - 6 * k;
    std::size_t o = i < 2 ? 1 : 5;
    x = 6 * k + o;
    for (i = (3 + o) / 2; !is_prime(x); x += i)
        i ^= 6;
    return x;
}*/