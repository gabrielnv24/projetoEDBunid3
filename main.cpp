#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int TABLE_SIZE = 100; 

struct Node {
    string palavra;
    int ocorrencias;
    Node* next;
    Node(string p) : palavra(p), ocorrencias(1), next(nullptr) {}
};

// Função hash 
int hashFunction(const string& word) {
    int hash = 0; 
    for (char c : word) {
        hash += static_cast<int>(c); // Soma o valor ASCII de cada caractere
    }
    return hash % TABLE_SIZE; // Aplica o módulo para garantir que o índice esteja dentro dos limites da tabela
}

class HashTable {
private:
    vector<Node*> tabela;

public:
    HashTable() {
        tabela.resize(TABLE_SIZE, nullptr);
    }

    // addText
    void addText(const string& texto) {
        stringstream ss(texto);
        string palavra;
        while (ss >> palavra) {
            int indice = hashFunction(palavra);
            Node* atual = tabela[indice];
            bool found = false;

            while (atual != nullptr) {
                if (atual->palavra == palavra) {
                    atual->ocorrencias++;
                    found = true;
                    break;
                }
                atual = atual->next;
            }

            if (!found) {
                Node* novo = new Node(palavra);
                novo->next = tabela[indice];
                tabela[indice] = novo;
            }
        }
        cout << "Texto adicionado. Contagem de palavras atualizada." << endl;
    }

    // countWord
    int countWord(const string& palavra) {
        int indice = hashFunction(palavra);
        Node* atual = tabela[indice];
        while (atual != nullptr) {
            if (atual->palavra == palavra) {
                return atual->ocorrencias;
            }
            atual = atual->next;
        }
        cout << "A palavra \"" << palavra << "\" não foi encontrada." << endl;
        return 0;
    }

    // updateWord
    void updateWord(const string& palavra, int novaContagem) {
        int indice = hashFunction(palavra);
        Node* atual = tabela[indice];
        while (atual != nullptr) {
            if (atual->palavra == palavra) {
                atual->ocorrencias = novaContagem;
                cout << "Contagem da palavra \"" << palavra << "\" atualizada para " << novaContagem << "." << endl;
                return;
            }
            atual = atual->next;
        }
        cout << "A palavra \"" << palavra << "\" não foi encontrada." << endl;
    }

    // removeWord
    void removeWord(const string& palavra) {
        int indice = hashFunction(palavra);
        Node* atual = tabela[indice];
        Node* anterior = nullptr;

        while (atual != nullptr) {
            if (atual->palavra == palavra) {
                if (anterior == nullptr) {
                    tabela[indice] = atual->next;
                } else {
                    anterior->next = atual->next;
                }
                delete atual;
                cout << "Palavra \"" << palavra << "\" removida." << endl;
                return;
            }
            anterior = atual;
            atual = atual->next;
        }
        cout << "A palavra \"" << palavra << "\" não foi encontrada." << endl;
    }

    // checkWord
    bool checkWord(const string& palavra) {
        int indice = hashFunction(palavra);
        Node* atual = tabela[indice];
        while (atual != nullptr) {
            if (atual->palavra == palavra) {
                cout << "A palavra \"" << palavra << "\" está presente e ocorre " << atual->ocorrencias << " vez(es)." << endl;
                return true;
            }
            atual = atual->next;
        }
        cout << "A palavra \"" << palavra << "\" não foi encontrada." << endl;
        return false;
    }

    // printTable
    void printTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Índice " << i << ": ";
            Node* atual = tabela[i];
            while (atual != nullptr) {
                cout << "(\"" << atual->palavra << "\", " << atual->ocorrencias << ") -> ";
                atual = atual->next;
            }
            cout << "NULL" << endl;
        }
    }
};

// CLI pra utilizar o sistema
void cli() {
    HashTable tabela;  
    string comando;

    while (true) {
        cout << "\nDigite um comando (addText, countWord, updateWord, removeWord, checkWord, printTable, exit): ";
        cin >> comando;

        if (comando == "addText") {
            cin.ignore(); 
            cout << "Digite o texto: ";
            string texto;
            getline(cin, texto);
            tabela.addText(texto);
        } 
        else if (comando == "countWord") {
            cout << "Digite a palavra: ";
            string palavra;
            cin >> palavra;
            int count = tabela.countWord(palavra);
            cout << "A palavra \"" << palavra << "\" ocorre " << count << " vez(es)." << endl;
        } 
        else if (comando == "updateWord") {
            cout << "Digite a palavra: ";
            string palavra;
            cin >> palavra;
            cout << "Digite a nova contagem: ";
            int novaContagem;
            cin >> novaContagem;
            tabela.updateWord(palavra, novaContagem);
        } 
        else if (comando == "removeWord") {
            cout << "Digite a palavra: ";
            string palavra;
            cin >> palavra;
            tabela.removeWord(palavra);
        } 
        else if (comando == "checkWord") {
            cout << "Digite a palavra: ";
            string palavra;
            cin >> palavra;
            tabela.checkWord(palavra);
        } 
        else if (comando == "printTable") {
            tabela.printTable();
        } 
        else if (comando == "exit") {
            cout << "Saindo..." << endl;
            break;
        } 
        else {
            cout << "Comando inválido!" << endl;
        }
    }
}

int main() {
    cli();
    return 0;
}
