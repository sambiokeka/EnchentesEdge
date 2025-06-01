# Medidor nível da água

Este projeto utiliza sensores de luz (LDR), sensor de distância ultrassônico (HC-SR04) e um sensor de umidade (DHT11), integrados com Arduino UNO, para monitorar o nível da água em enchentes e controlar LEDs, um buzzer e dois displays LCD, com base em diferentes condições.

## Autores

- Erick Jooji (RM: 564482)
- Luiz Dalboni (RM: 564189)
- Matheus Tozarelli (RM: 563490)
- Rafael Lorenzini (RM: 563643)

---

## Ferramentas e Tecnologias

- **Linguagem de programação:** C++
- **Placa:** Arduino UNO
- **Simulação:** [Tinkercad - Projeto SensorLuz](https://www.tinkercad.com/things/1FLMw0RI0Qp-alarme-2/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU)

---

## Descrição Geral

O **Medidor de Enchentes** é parte do projeto da Global Solution, que visa auxiliar civis em situações de alagamentos em ruas residenciais durante chuvas intensas. O sistema monitora o nível de água e a umidade do solo e apresenta informações em tempo real nos displays LCD, acionando alertas visuais e sonoros conforme o risco identificado.

---

## Funcionalidades Principais

- **Medição do nível da água:** Utiliza sensor ultrassônico para identificar a altura da água.
- **Leitura da umidade:** Mede a umidade do ar via sensor analógico DHT11.
- **Alertas visuais e sonoros:** LEDs e buzzer sinalizam o grau de perigo de alagamento.
- **Exibição de informações:** Dois displays LCD mostram o nível da água, umidade e previsões para a enchente.
- **Média móvel:** O sistema suaviza leituras usando buffers circulares para maior confiabilidade.

---

## Componentes Utilizados

- **1** Resistor de 1kΩ (para o LDR)
- **7** Resistores de 220Ω (para os LEDs)
- **25** Jumpers
- **3** LEDs (Vermelho, Amarelo, Verde)
- **1** Buzzer
- **1** DHT11 (Para sensor de Umidade)
- **2** Displays LCD com módulo I2C

---

## Estrutura do Código

### 1. Bibliotecas e Definições

- `LiquidCrystal_I2C`: Biblioteca para controle dos displays LCD via I2C.
- Definições de pinos para sensores, LEDs e buzzer.

### 2. Inicialização de Componentes

- Dois objetos `LiquidCrystal_I2C` para os displays.
- Definição dos pinos dos sensores, LEDs e buzzer.
- Buffers circulares para armazenar as últimas leituras de umidade e altura da água.

### 3. Funções Principais

- **microsegundosParaCentimetros:** Converte o tempo de resposta do sensor ultrassônico em centímetros.
- **inicializaBuffers:** Preenche os buffers de médias iniciais para evitar leituras instáveis ao ligar.
- **calculaMedia:** Calcula a média dos valores em um buffer.
- **atualizaMedias:** Atualiza os buffers e calcula as médias de umidade e altura.
- **processaUMIDADE / processaALTURA:** Classifica as leituras em cenários de risco (baixa, média ou alta umidade/nível de água).
- **atualizaDisplay:** Alterna as informações mostradas nos displays LCD a cada 5 segundos, exibindo:
  - Nível da água e grau de perigo.
  - Umidade do solo e previsão de tendência (aumentar/diminuir enchente).

### 4. Loop Principal

A cada intervalo (~500ms):

- Aciona o sensor ultrassônico e lê o tempo de resposta.
- Lê o sensor de umidade.
- Calcula médias suavizadas.
- Determina o nível de risco e atualiza LEDs e buzzer:
  - **LED Verde:** Nível seguro.
  - **LED Amarelo:** Atenção (nível intermediário).
  - **LED Vermelho + Buzzer:** Perigo (nível alto).
- Atualiza os displays com as informações atuais.

---

## Esquemático de Conexão 

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

## Exemplo Visual

![Exemplo do sistema funcionando](https://github.com/user-attachments/assets/6da0edb6-8746-43d5-b18e-2a621af844fc)

---

## Como Usar

1. Faça o upload do código `sensorOndas.ino` para o Arduino UNO.
2. Conecte os sensores, LEDs, buzzer e displays conforme a tabela acima.
3. Alimente o sistema e observe as leituras e alertas nos displays LCD, LEDs e buzzer.
4. O sistema alterna automaticamente entre informações do nível da água/perigo e umidade/previsão.

---

## Possíveis Melhorias

- Adicionar comunicação sem fio para envio de alertas remotos.
- Registro das leituras em cartão SD.
- Integração com outros sensores ambientais (ex: pluviômetro).

---

## Licença

Este projeto está sob a licença MIT.

---

**Equipe:** Projeto EnchentesEdge – sambiokeka
