#include <stdio.h>
#include "matriks.h"
#include "boolean.h"

void MakeMATRIKS (int NB, int NK, MATRIKS * M){
    M->NBrsEff = NB;
    M->NKolEff = NK;
    
    int i,j;
    for (i = 0; i < NB; i++){
        for (j = 0; j < NK; j++){
            M->Mem[i][j] = 0;
        }
    }
}

boolean IsIdxValid (int i, int j){
    return (i >= BrsMin && i <= BrsMax && j >= KolMin && j <= KolMax);
}

indeks GetFirstIdxBrs (MATRIKS M){
    return BrsMin;
}

indeks GetFirstIdxKol (MATRIKS M){
    return KolMin;
}

indeks GetLastIdxBrs (MATRIKS M){
    return M.NBrsEff-1;
}

indeks GetLastIdxKol (MATRIKS M){
    return M.NKolEff-1;
}

boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
    return (i >= GetFirstIdxBrs(M) && i <= GetLastIdxBrs(M) && j >= GetFirstIdxKol(M) && j <= GetLastIdxKol(M));
}

ElType GetElmtDiagonal (MATRIKS M, indeks i){
    return M.Mem[i][i];
}

void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
    MakeMATRIKS(MIn.NBrsEff, MIn.NKolEff, MHsl);

    int i,j;
    for (i = GetFirstIdxBrs(*MHsl); i <= GetLastIdxBrs(*MHsl); i++){
        for (j = GetFirstIdxKol(*MHsl); j <= GetLastIdxKol(*MHsl); j++){
            MHsl->Mem[i][j] = MIn.Mem[i][j];
        }
    }
}

void BacaMATRIKS (MATRIKS * M, int NB, int NK){
    MakeMATRIKS(NB, NK, M);

    int i,j;
    for (i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); i++){
        for (j = GetFirstIdxKol(*M); j <= GetLastIdxKol(*M); j++){
            scanf("%d", &(M->Mem[i][j]));
        }
    }
}

void TulisMATRIKS (MATRIKS M){
    int i,j;
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
        for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++){
            printf((
                (j != GetLastIdxKol(M)) ? "%d " : 
                ((i != GetLastIdxBrs(M)) ? "%d\n" : "%d")
                ), M.Mem[i][j]);
        }
    }
}
                              
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2){
    MATRIKS MR;
    MakeMATRIKS(M1.NBrsEff, M1.NKolEff, &MR);

    int i,j;
    for (i = GetFirstIdxBrs(MR); i <= GetLastIdxBrs(MR); i++){
        for (j = GetFirstIdxKol(MR); j <= GetLastIdxKol(MR); j++){
            MR.Mem[i][j] = M1.Mem[i][j] + M2.Mem[i][j];
        }
    }
    return MR;
}

MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2){
    MATRIKS MR;
    MakeMATRIKS(M1.NBrsEff, M1.NKolEff, &MR);

    int i,j;
    for (i = GetFirstIdxBrs(MR); i <= GetLastIdxBrs(MR); i++){
        for (j = GetFirstIdxKol(MR); j <= GetLastIdxKol(MR); j++){
            MR.Mem[i][j] = M1.Mem[i][j] - M2.Mem[i][j];
        }
    }
    return MR;
}

MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2){
    MATRIKS M;
    MakeMATRIKS(M1.NBrsEff, M1.NKolEff, &M);
    int i, j, k;
    for(i  = GetFirstIdxBrs(M1); i <= GetLastIdxBrs(M1); i++){
        for(j = GetFirstIdxKol(M2); j <= GetLastIdxKol(M2); j++){
            for(k = GetFirstIdxKol(M1); k <= GetLastIdxKol(M1); k++){
                Elmt(M, i, j) += (Elmt(M1, i, k)*Elmt(M2, k, j));
            }
        }
    }
    return M;
}

MATRIKS KaliKons (MATRIKS M, ElType X){
    MATRIKS MR;
    MakeMATRIKS(M.NBrsEff, M.NKolEff, &MR);

    int i,j;
    for (i = GetFirstIdxBrs(MR); i <= GetLastIdxBrs(MR); i++){
        for (j = GetFirstIdxKol(MR); j <= GetLastIdxKol(MR); j++){
            MR.Mem[i][j] = X*M.Mem[i][j];
        }
    }
    return MR;
}

void PKaliKons (MATRIKS * M, ElType K){
    MATRIKS MNew = KaliKons(*M, K);
    *M = MNew;
}

boolean EQ (MATRIKS M1, MATRIKS M2){
    boolean result = NBElmt(M1) == NBElmt(M2);
    int i,j;
    int baris1 = GetFirstIdxBrs(M1) >= GetFirstIdxBrs(M2) ? GetFirstIdxBrs(M1) : GetFirstIdxBrs(M2);
    int baris2 = GetLastIdxBrs(M1) <= GetLastIdxBrs(M2) ? GetLastIdxBrs(M1) : GetLastIdxBrs(M2);
    int kol1 = GetFirstIdxKol(M1) >= GetFirstIdxKol(M2) ? GetFirstIdxKol(M1) : GetFirstIdxKol(M2);
    int kol2 = GetLastIdxKol(M1) <= GetLastIdxKol(M2) ? GetLastIdxKol(M1) : GetLastIdxKol(M2);
    for (i = baris1; i <= baris2; i++){
        for (j = kol1; j <= kol2; j++){
            result = result && (M1.Mem[i][j] == M2.Mem[i][j]);
        }
    }
    return result;
}

boolean NEQ (MATRIKS M1, MATRIKS M2){
    return (!EQ(M1, M2));
}

boolean EQSize (MATRIKS M1, MATRIKS M2){
    return (M1.NBrsEff == M2.NBrsEff && M1.NKolEff == M2.NKolEff);
}

int NBElmt (MATRIKS M){
    return (M.NBrsEff*M.NKolEff);
}

boolean IsBujurSangkar (MATRIKS M){
    return (M.NBrsEff == M.NKolEff);
}

boolean IsSimetri (MATRIKS M){
    boolean result = IsBujurSangkar(M);
    int i,j;
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
        for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++){
            result = result && (M.Mem[i][j] == M.Mem[j][i]);
        }
    }
    return result;
}

boolean IsSatuan (MATRIKS M){
    boolean result = IsBujurSangkar(M);
    if (result){
        int i,j;
        for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
            for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++){
                result = result && ((i != j) ? (M.Mem[i][j] == 0) : (M.Mem[i][j] == 1));
            }
        }
    }
    return result;
}

boolean IsSparse (MATRIKS M){
    int nonzero = 0,i,j;

    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
        for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++){
            nonzero += (M.Mem[i][j] == 0 ? 0 : 1);
        }
    }

    return (20*nonzero <= NBElmt(M));
}

MATRIKS Inverse1 (MATRIKS M){
    return KaliKons(M, -1);
}

float Determinan (MATRIKS M){
    int size = NBrsEff(M);
    float m[size][size];
    int i, j;

    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            m[i][j] = Elmt(M, i, j);
        }
    }

    float temp, result = 1;
    boolean swap;
    int swapped = 0;

    while (size > 0){
        swap = false;
        i = 0;
        if (m[size-1][size-1] == 0){
            while (i < (size-1) && !swap){
                if (m[size-1][size-1] == 0){
                    i++;
                } else {
                    swap = true;
                }
            }
        }
        if (i == (size-1) && (size > 1)){
            return 0;
        } else if (swap){
            for(j = 0; j < size; j++){
                temp = m[size-1][j];
                m[size-1][j] = m[i][j];
                m[i][j] = temp;
            }
        }
        for (i = 0; i < (size-1); i++){
            for(j=0; j<size; j++){
                m[i][j] -= m[size-1][j]*(m[i][size-1]/m[size-1][size-1]);
            }
        }
        result *= m[size-1][size-1];
        swapped = (swapped+(swap ? 1 : 0))%2;
        size--;
    }
    return (result*(swapped==0 ? 1 : -1));
}

void PInverse1 (MATRIKS * M){
    MATRIKS MNew = Inverse1(*M);
    *M = MNew;
}

void Transpose (MATRIKS * M){
    MATRIKS MNew;
    MakeMATRIKS(M->NBrsEff, M->NKolEff, &MNew);

    int i,j;
    for (i = GetFirstIdxBrs(MNew); i <= GetLastIdxBrs(MNew); i++){
        for (j = GetFirstIdxKol(MNew); j <= GetLastIdxKol(MNew); j++){
            MNew.Mem[i][j] = M->Mem[j][i];
        }
    }

    *M = MNew;
}