/*
a)
supongamos que tenemos una funcion isPalabra(s) que toma una cadena s y devuelve si es una palabra o no.

isPalabra(s) -> O(|s|), 

Ahora tenemos una cadena de caracteres  

isSubDivisibles(s){
  if(s.size() == 0){
    return True;
  }
  Bool res = False;

  for(int i = 1; i<=|s|; i++){
    res = res || (isPalabra(s[0:i]) && isSubDivisible(s[i:|s|])) //Notacion s[a:b] desde a hasta b-1 (b no inclsuive)
  }

  return res;
}
*/

/*
  b)

  cuando i=1
  se llama palabra('a') = O(1) + T(n-1)
  
  cuando i=2
  se llama palabra('aa') = O(2) + T(n-2)
  
  ...
  ...
  ...

  cuando i=n-1
  se llama palabra('aa....a') = O(n-1) + T(1)

  cuando i=n
  se llama palabra('aa....aa') = O(n) + T(0)
  
  Hubo n llamados. 
  
  T(n) = i=0Ei=(n-1) T(i) + O(n)

  T(n-1) = i=0Ei=(n-2) T(i) + O(n-1)

  // O(n) tomamos c*n
  T(n) - T(n-1) = T(n-1) + C
  T(n) = 2T(n-1) + C
  T(n) = 2(2T(n-2) + C) + C = 4T(n-2) + 3C 
  T(n) = 4(2T(n-3) + C) + 3C = 8T(n-3) + 7C 
  ...
  T(n) = 2**n * T(0) + C*(2**(n-1) + ... + 2 + 1) = O(2**n)

  son 2**n llamados de palabra.

  Costo Total = O(O(palabra)*2**n)

  Si la palabra tiene tamano n, entonces 

*/
