# sensorOndas.ino – Detalhamento do Código

Este código Arduino é parte do projeto **EnchentesEdge**, que visa auxiliar civis em situações de alagamentos em ruas residenciais durante chuvas intensas. O programa utiliza sensores de umidade e ultrassônicos para medir o nível da água e umidade do solo, exibindo essas informações em dois displays LCD, acionando LEDs de alerta e um buzzer em situações de risco.

---

## Funcionalidades Principais

- **Medição do nível da água:** Utiliza um sensor ultrassônico para identificar a altura da água.
- **Leitura da umidade:** Mede a umidade do solo usando um sensor analógico.
- **Alertas visuais e sonoros:** LEDs e buzzer sinalizam o grau de perigo de alagamento.
- **Exibição de informações:** Dois displays LCD mostram o nível da água, a umidade e previsões.
- **Média móvel:** O sistema suaviza leituras usando buffers circulares para evitar falsos alarmes.

---

## Estrutura do Código

### 1. Bibliotecas e Definições

- `LiquidCrystal_I2C`: Biblioteca para controle dos displays LCD via I2C.
- Definições de pinos para sensores, LEDs e buzzer.

### 2. Inicialização de Componentes

- Dois objetos `LiquidCrystal_I2C` para os displays.
- Definição dos pinos dos sensores, LEDs e buzzer.
- Buffers para armazenar as últimas leituras de umidade e altura.

### 3. Funções Principais

#### **microsegundosParaCentimetros**
Converte o tempo de resposta do sensor ultrassônico em centímetros.

#### **inicializaBuffers**
Preenche os buffers de médias iniciais para evitar leituras erráticas ao ligar.

#### **calculaMedia**
Calcula a média dos valores em um buffer.

#### **atualizaMedias**
Atualiza os buffers circulares e calcula as médias de umidade e altura.

#### **processaUMIDADE / processaALTURA**
Classifica as leituras em cenários de risco (baixa, média ou alta umidade/nível de água).

#### **atualizaDisplay**
Alterna as informações mostradas nos displays LCD a cada 5 segundos, exibindo:
- Nível da água e grau de perigo.
- Umidade e previsão de tendência (aumentar/diminuir).

### 4. Loop Principal

A cada intervalo (~500ms):
- Ativa o sensor ultrassônico e lê o tempo de resposta.
- Lê o sensor de umidade.
- Calcula médias suavizadas.
- Determina o nível de risco e atualiza LEDs e buzzer:
  - **LED Verde:** Nível seguro.
  - **LED Amarelo:** Atenção (nível médio).
  - **LED Vermelho + Buzzer rápido:** Perigo (nível alto).
- Atualiza os displays com as informações atuais.

---

## Esquemático de Conexão (Sugestão)

| Componente         | Pino Arduino |
|--------------------|-------------|
| Sensor Ultrassônico| 7           |
| Sensor Umidade     | A0          |
| LCD 1              | I2C (39)    |
| LCD 2              | I2C (38)    |
| LED Verde          | 11          |
| LED Amarelo        | 12          |
| LED Vermelho       | 13          |
| Buzzer             | 10          |

---

## Como Usar

1. Faça o upload do código `sensorOndas.ino` para seu Arduino.
2. Conecte os sensores, LEDs, buzzer e displays conforme a tabela acima.
3. Alimente o sistema e observe a leitura nos displays e os alertas visuais/sonoros.
4. O sistema alterna automaticamente entre informações de nível d’água/perigo e umidade/previsão.

---

## Possíveis Melhorias

- Adicionar comunicação sem fio para enviar alertas remotos.
- Registro de histórico de leituras em cartão SD.
- Integração com outros sensores ambientais.

---

## Licença

Este projeto está sob a licença MIT.

---

**Autor:** Projeto EnchentesEdge – sambiokeka