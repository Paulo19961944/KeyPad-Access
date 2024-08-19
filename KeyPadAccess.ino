// INCLUSÃO DE BIBLIOTECAS
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// VARIAVEIS GLOBAIS
const int MAX_ATTEMPTS = 3; // Número máximo de tentativas
const char *CORRECT_CODE = "122024"; // Código correto
const byte PIN_RELAY = 3; // Pino do Relé
const byte PIN_BUTTON = 2; // Pino do Botão
unsigned int LAST_KEY_TIME = 0; // Define o Tempo Anterior
unsigned int DEBOUNCE_BUTTON = 50; // Debounce do Botão

LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço do I2C e dimensões do LCD (colunas, linhas)

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
int rowCount = sizeof(rows) / sizeof(rows[0]);
int colCount = sizeof(cols) / sizeof(cols[0]);
Keypad kdp(makeKeymap(keyMap), rows, cols, rowCount, colCount);

// TENTATIVAS
String inputCode = ""; // Armazena o código digitado
int attempts = 0; // Contador de tentativas
bool accessBlocked = false; // Flag para indicar se o acesso está bloqueado

// SETUP INICIAL
void setup() {
  Serial.begin(9600); // Inicializa a Serial
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  lcd.begin(16, 2); // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.backlight(); // Liga a luz de fundo do LCD
  digitalWrite(PIN_RELAY, LOW); // Garante que o relé comece apagado
}

// FUNÇÃO LOOP
void loop() {
  unsigned int currentTime = millis();
  if (digitalRead(PIN_BUTTON) == LOW && (currentTime - LAST_KEY_TIME) > DEBOUNCE_BUTTON) { // Botão pressionado
    digitalWrite(PIN_RELAY, LOW); // Desliga o relé
    delay(1000); // Pequeno atraso para evitar leitura constante
  }

  if (accessBlocked) {
    // Se o acesso está bloqueado, não faz nada além de verificar o botão
    return;
  }

  keyPadAccess(); // Chama a Função keyPadAccess
}

// FUNÇÃO DE ACESSO DO KEYPAD
void keyPadAccess() {
  char key = kdp.getKey(); // Captura a tecla do Keypad

  // SE CLICAR EM ALGUMA TECLA
  if (key != NO_KEY) {
    lcd.clear(); // Limpa o LCD para mostrar a nova mensagem

    if (key == '#') { // # É usado para confirmar o código
      if (inputCode == CORRECT_CODE) {
        inputCode = ""; // Reseta o código após sucesso
        attempts = 0; // Reseta as tentativas
        digitalWrite(PIN_RELAY, HIGH); // Liga o relé
        lcd.print("Acesso Liberado");
        clearLCD();
      } else {
        attempts++;
        if (attempts >= MAX_ATTEMPTS) {
          lcd.print("Acesso Bloqueado");
          accessBlocked = true; // Define a flag para bloquear o acesso
        } else {
          lcd.print("Acesso Negado");
          clearLCD();
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

// LIMPA O DISPLAY
void clearLCD(){
  delay(1000); // Espera 1 segundo
  lcd.clear(); // Limpa o Display
}
