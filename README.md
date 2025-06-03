# Medidor de Nível da Água

Este projeto utiliza sensores de luz (LDR), um sensor de distância ultrassônico (HC-SR04) e um sensor de umidade do solo, integrados com o Arduino UNO, para monitorar o nível da água em enchentes e a previsão de ela diminuir ou aumentar. O sistema aciona LEDs, um buzzer e dois displays LCD com base nas condições medidas.

- **Link do video:** https://youtu.be/WvmeCM9WY6k

---

## Autores

- Erick Jooji (RM: 564482)  
- Luiz Dalboni (RM: 564189)  
- Matheus Tozarelli (RM: 563490)  
- Rafael Lorenzini (RM: 563643)

---

## Ferramentas e Tecnologias

- **Linguagem:** C++  
- **Placa:** Arduino UNO  
- **Simulação:** [Tinkercad - Projeto SensorLuz](https://www.tinkercad.com/things/1FLMw0RI0Qp-alarme-2/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU)

---

## Descrição Geral

O **Medidor de Enchentes** é parte da solução desenvolvida para o projeto Global Solution, com o objetivo de auxiliar civis em situações de alagamento em áreas residenciais. O sistema monitora em tempo real a altura da água e a umidade do solo, apresentando essas informações nos displays LCD e acionando alertas visuais e sonoros.

---

## Funcionalidades

- **Medição do nível da água:** Sensor HC-SR04 calcula a altura da lâmina d'água.
- **Medição da umidade do solo:** Sensor de umidade do solo detecta a umidade relativa do solo.
- **Alertas visuais e sonoros:** LEDs e buzzer indicam o nível de risco.
- **Displays LCD:** Exibem o status atual do nível da água e umidade.
- **Média móvel:** Leitura contínua e suavizada via buffers circulares (3 para altura e 5 para umidade do solo).

---

## Componentes Utilizados

- **3** Resistores de 220Ω  
- **3** LEDs (Verde, Amarelo, Vermelho)  
- **1** Buzzer  
- **1** Sensor Ultrassônico HC-SR04  
- **1** Sensor de Umidade do Solo  
- **2** Displays LCD com módulo I2C  
- **Jumpers** e **protoboard**

---

## Estrutura do Código

### 1. Bibliotecas e Configurações Iniciais

- `LiquidCrystal_I2C`: Comunicação com displays LCD.
- Definições dos pinos utilizados e variáveis de controle.

### 2. Inicialização de Componentes

- Criação dos objetos dos LCDs.
- Definição dos pinos dos sensores, LEDs e buzzer.
- Inicialização dos buffers circulares.

### 3. Funções Principais

- **`microsegundosParaCentimetros()`** – Converte tempo do ultrassônico em centímetros.
- **`inicializaBuffers()`** – Preenche buffers com leituras iniciais.
- **`calculaMedia()`** – Calcula média de valores em buffers.
- **`atualizaMedias()`** – Atualiza e calcula novas médias de leitura.
- **`processaUmidadeSOLO()` / `processaALTURA()`** – Classifica risco com base em médias.
- **`atualizaDisplay()`** – Alterna conteúdo dos LCDs entre:
  - Nível da água e risco.
  - Umidade do solo e previsão (subida/queda da enchente).

### 4. Loop Principal

Executado a cada ~500ms:

- Ativa o sensor ultrassônico e mede a altura da água.
- Lê a umidade do solo.
- Calcula as médias e atualiza status de risco.
- Aciona o LED correspondente:
  - **Verde:** Nível seguro
  - **Amarelo:** Alerta
  - **Vermelho + Buzzer:** Perigo 
- Exibe informações nos displays LCD.

---

## Esquemático de Conexão

| Componente           | Pino Arduino |
|----------------------|--------------|
| Sensor Ultrassônico  | 7 (ver nota abaixo) |
| Sensor Umidade       | A0           |
| LCD 1                | I2C (39)     |
| LCD 2                | I2C (38)     |
| LED Verde            | 11           |
| LED Amarelo          | 12           |
| LED Vermelho         | 13           |
| Buzzer               | 10           |


---

## Como Usar

1. Faça upload do código `sensorOndas.ino` para o Arduino UNO.
2. Conecte os sensores, LEDs, buzzer e displays conforme a tabela acima.
3. Alimente o sistema e monitore os alertas nos displays, LEDs e buzzer.
4. O sistema alterna automaticamente entre as leituras de altura e umidade.

---

![Exemplo do sistema funcionando](https://github.com/user-attachments/assets/6da0edb6-8746-43d5-b18e-2a621af844fc)
