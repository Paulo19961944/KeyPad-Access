// INCLUSÃO DA BIBLIOTECA KEYPAD
#include <Keypad.h>

// VARIAVEIS GLOBAIS
const int MAX_ATTEMPTS = 3; // Número máximo de tentativas
const char *CORRECT_CODE = "122024"; // Código correto
const byte PIN_RELAY = 3;

// TECLAS DO KEYPAD
char keyMap[][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// CONFIGURAÇÃO DO KEYPAD
byte rows[] = {12, 11, 10, 9};
byte cols[] = {7, 6, 5, 4};
int tam = sizeof(rows) / sizeof(rows[0]);
Keypad kdp(makeKeymap(keyMap), rows, cols, tam, tam);

// TENTATIVAS
String inputCode = ""; // Armazena o código digitado
int attempts = 0; // Contador de tentativas
bool accessBlocked = false; // Flag para indicar se o acesso está bloqueado

// SETUP INICIAL
void setup() {
  Serial.begin(9600); // Inicializa a Serial
  pinMode(PIN_RELAY, OUTPUT);
}

// FUNÇÃO LOOP
void loop() {
  // BLOQUEIA O ACESSO
  if (accessBlocked) {
    // Se o acesso está bloqueado, não faz nada
    return;
  }

  keyPadAccess(); // Chama a Função keyPadAccess
}

// FUNÇÃO DE ACESSO DO KEYPAD
void keyPadAccess(){
  char key = kdp.getKey(); // Captura a tecla do Keypad

  // SE CLICAR EM ALGUMA TECLA
  if (key != NO_KEY) {
    if (key == '#') { // # É usado para confirmar o código
      if (inputCode == CORRECT_CODE) {
        Serial.println("Acesso Liberado");
        inputCode = ""; // Reseta o código após sucesso
        attempts = 0; // Reseta as tentativas
        digitalWrite(PIN_RELAY, HIGH);
      } else {
        attempts++;
        if (attempts >= MAX_ATTEMPTS) {
          Serial.println("Acesso Bloqueado");
          accessBlocked = true; // Define a flag para bloquear o acesso
        } else {
          Serial.println("Acesso Negado");
        }
        inputCode = ""; // Reseta o código após falha
      }
    } else if (key == '*') { // * É usado para apagar o último caractere
      if (inputCode.length() > 0) {
        inputCode.remove(inputCode.length() - 1); // Remove o último caractere
      }
    } else {
      inputCode += key; // Adiciona a tecla digitada ao código
    }
  }
}
