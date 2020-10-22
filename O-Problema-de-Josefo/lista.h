typedef struct pessoa Pessoa;
typedef struct lista Lista;

Lista* CriarLista();
int ListaVazia(Lista *pLista);
int Insere(Lista *pLista, int x);
void PreencheLista(Lista *pLista, int n);
int Remove(Lista *pLista, Pessoa *x);
int RemoveIndex(Lista *pLista, int k);
void Destroi(Lista *pLista);
