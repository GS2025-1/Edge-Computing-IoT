💧 Projeto: Monitor de Nível da Água com Alerta de Chuva


📌 Descrição do Problema
Em períodos de chuva intensa, regiões ribeirinhas como as próximas ao Rio Taquari enfrentam riscos de alagamentos e enchentes. A ausência de sistemas de alerta acessíveis e preventivos coloca em risco a segurança da população local, dificultando a reação dos moradores e das autoridades.

🧠 Visão Geral da Solução
Este projeto implementa um sistema de monitoramento do nível da água, com alerta de chuva e notificações visuais e sonoras. Ele utiliza um sensor ultrassônico para medir a altura da água, um botão para simular a ocorrência de chuva, LEDs e buzzer para alertas, além de um display LCD I2C para exibir as informações em tempo real.

🧱 Componentes Utilizados
Arduino Uno

Sensor ultrassônico HC-SR04

Display LCD 20x4 com módulo I2C

LEDs: verde, amarelo e vermelho

Buzzer (ativo ou passivo)

Botão de pressão (simulando chuva)

Jumpers e protoboard

📋 Instruções de Funcionamento
1. Leitura do Nível da Água
O sensor HC-SR04 mede a distância da água até o sensor.

A lógica de risco é a seguinte:

> 100 cm → Situação normal (LED verde)

51 a 100 cm → Situação de atenção (LED amarelo)

≤ 50 cm → Situação crítica (LED vermelho + buzzer intermitente)

2. Simulação de Chuva
O botão conectado ao pino 8 representa a chuva:

Pressionado (LOW) = Chovendo

Solto (HIGH) = Tempo seco

3. Display LCD
Exibe:

Nível da água em cm

Status da situação (OK, Atenção ou Crítico)

Informação sobre chuva

Alerta de RISCO DE ALAGAMENTO se chover durante nível crítico

📊 Layout do LCD
Linha 0: Nivel: 85 cm
Linha 1: Status: Atencao
Linha 2: Chovendo cuidado
Linha 3: RISCO ALAGAMENTO

📍 Guia de Simulação no Wokwi
Acesse o link:
🔗 https://wokwi.com/projects/432152361386563585

Clique em "Start Simulation".

Para simular chuva:

Clique no botão azul no canto superior direito do Arduino para pressioná-lo.

Para simular o nível da água:

Clique no sensor HC-SR04 e altere a distância (em cm).

📸 Figura Ilustrativa 
[Imagem do protótipo](image.png)

🔗 Links Importantes
💻 Simulador Wokwi:
👉 https://wokwi.com/projects/432152361386563585

🎥 Vídeo Demonstrativo:
👉 https://youtu.be/5JOB0prDq1M