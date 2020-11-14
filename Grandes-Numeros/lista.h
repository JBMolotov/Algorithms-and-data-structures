typedef struct no No;
typedef struct lista Lista;

Lista* Cria();
void InsereInicio(Lista *l, int x);
void InsereFim(Lista *l, int x);
void Negativar(Lista *l);
void Imprime(Lista *l);
int Tamanho(Lista *l);
void Destroi(Lista *l);
Lista* Limpa(Lista *l);
int Igual(Lista *num1, Lista *num2);
int Maior(Lista *num1, Lista *num2);
Lista* Soma(Lista *num1, Lista *num2);