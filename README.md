# Data Broadcasting Project with nRF24L01 Module

This project aims to create a data broadcasting system using the nRF24L01 transceiver module for wireless transmission and reception. It includes a web interface on the transmitter side to control and manage the broadcasting process. The output at the receiver side is displayed on an SSD1306 OLED display, and critical words can be triggered using a red LED or buzzer at the receiving side.

## Features

- Utilizes the nRF24L01 module for reliable wireless communication.
- Transmitter side equipped with the nRF24L01 module for data transmission.
- Receivers equipped with the nRF24L01 module for data reception.
- Web interface on the transmitter side for easy control and management.
- Efficient dissemination of data to multiple receivers.
- Real-time monitoring and control of the broadcasting process.
- Output displayed on an SSD1306 OLED display at the receiver side.
- Critical words trigger a red LED or buzzer at the receiving side.

## Getting Started

### Prerequisites

- Arduino IDE (or any compatible IDE)
- nRF24L01 library (install via Arduino Library Manager)

### Hardware Setup

1. Connect the nRF24L01 module to the transmitter esp8266 or any board with wifi capability.
2. Connect the nRF24L01 module to the receiver Arduino board(s).
3. Connect the SSD1306 OLED display to the receiver Arduino board.
4. Connect the red LED or buzzer to the receiver Arduino board.

### Software Setup

1. Clone this repository to your local machine.
2. Open the transmitter and receiver sketches in Arduino IDE.
3. Configure the necessary settings (e.g., transmission address, data rate) in the sketches.
4. Upload the sketches to the respective Arduino boards.

## Usage

1. Power on the transmitter and receiver devices.
2. Access the web interface on the transmitter side through a web browser.
3. Use the web interface to control and manage the data broadcasting process.
4. The transmitted data will be received by the nRF24L01 modules on the receiver side.
5. The received data will be displayed on the SSD1306 OLED display.
6. If critical words are detected in the received data, the red LED or buzzer will be triggered accordingly.

## Contributing

Contributions to this project are welcome. Please feel free to submit pull requests or open issues for any enhancements or bug fixes.

## License

This project is licensed under the [GNU GPL](LICENSE).
