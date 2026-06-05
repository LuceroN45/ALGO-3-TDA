
b = [8, 4, 7, 6, 5, 1, 3, 2]
c = [8, 6, 7, 4, 5, 1, 3, 2]

def izq_dominante (a):
  if len(a) == 2 : #caso base
    if a[0] > a[1]:
      return True
    else :
      return False
    
  #Divide
  primera_mitad = a[:len(a)//2]
  segunda_mitad = a[len(a)//2:]
  
  if (sum(primera_mitad) > sum(segunda_mitad)):
    return izq_dominante(primera_mitad) & izq_dominante(segunda_mitad) #Conquer
  else:
    return False

aca = [-4, -1, 2, 4, 7]

def indice_espejo (a,izq = 0,der = None):
  if der == None:
    der = len(a)
    
  if izq == der :
    return a[izq] == izq + 1
    
  medio = (izq + der) // 2
  
  if medio + 1 == a[medio]:
    return True
  elif medio + 1 > a[medio]:
    return indice_espejo(a,medio,der)
  elif medio + 1 < a[medio]:
    return indice_espejo(a,izq,medio)
  
def potencia_logaritmica(a,b):
  if b == 0:
    return 1
  if b == 1:
    return a
  
  if b%2 == 0 :
    return potencia_logaritmica(a*a,b//2)
  else:
    return a*potencia_logaritmica(a,b-1)


def conjuncion(a,i_0,i_1,j_0,j_1):
  i = i_0
  conjuncion = True;
  while i < i_1:
    j = j_0
    while j < j_1:
      conjuncion = conjuncion & a[i][j]
      if not (conjuncion):
        break
      j += 1
    i += 1
    
  return conjuncion
        
      
    

def solve(i0, i1, j0, j1):
    # Base case: we are in a 1x1 matrix (or empty due to edge cases)
    if (i0 + 1 == i1 and j0 + 1 == j1) or (i0 == i1 and j0 == j1):
        # If the matrix is 1x1, we check if the value is False
        if mat[i0][j0] == False:
            return (i0, j0)
        else:
            return (-1, -1)

    else:
        # Calculate midpoints for rows and columns
        ideltaMitad = (i1 - i0) // 2
        jdeltaMitad = (j1 - j0) // 2
        iHalf = i0 + ideltaMitad
        jHalf = j0 + jdeltaMitad

        # Top-left quadrant
        if not conjuncion(i0, iHalf, j0, jHalf):
            return solve(i0, iHalf, j0, jHalf)
        
        # Bottom-left quadrant
        elif not conjuncion(iHalf, i1, j0, jHalf):
            return solve(iHalf, i1, j0, jHalf)
        
        # Top-right quadrant
        elif not conjuncion(i0, iHalf, jHalf, j1):
            return solve(i0, iHalf, jHalf, j1)
        
        # Bottom-right quadrant
        elif not conjuncion(iHalf, i1, jHalf, j1):
            return solve(iHalf, i1, jHalf, j1)

        # No False values were found in any quadrant
        return (-1, -1)
  
  
prueba = [[True,True,True,True],
          [True,True,True,True],
          [True,True,True,True],
          [True,True,True,False]]
respuesta = (3,3)

print(cazador_de_falsos(prueba))