/*
 * PostLab4_C.c
 *
 * Created: 4/11/2026
 * Author : mynor
 */ 



#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// --- Prototipos ---
void initADC(void);
void setSegments(uint8_t nibble);
void dec_hex(uint8_t val);

// --- Variables ---
volatile int contador = 0;
volatile int contadorADC = 0;
int LowNibble = 0;
int HighNibble = 0;

unsigned char hexaDisplay[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

int main(void)
{
	cli();
	
	// 1. CONFIGURACIÓN DE SALIDAS
	DDRD |= (1 << DDD5) | (1 << DDD6) | (1 << DDD7) | (1 << DDD0) | (1 << DDD1) | (1 << DDD2);
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);
	DDRC |= 0x3F;

	// 2. ENTRADAS (Botones D3 y D4)
	DDRD &= ~((1 << DDD3) | (1 << DDD4));
	PORTD |= (1 << PORTD3) | (1 << PORTD4);

	UCSR0B = 0; // Desactivar UART para liberar D0 y D1

	// 3. INTERRUPCIONES PCINT (Puerto D)
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT19) | (1 << PCINT20);

	initADC();
	sei();

	while (1)
	{
		// --- LEDs BINARIOS (D5-D12) ---
		if (contador > 255) contador = 0;
		if (contador < 0)   contador = 255;
		PORTD = (PORTD & ~0xE0) | ((contador & 0x07) << 5);
		PORTB = (PORTB & ~0x1F) | ((contador >> 3) & 0x1F);

		// --- BANDERA COMPARADORA (D13) ---
		if (contador == contadorADC) PORTB |= (1 << PORTB5);
		else PORTB &= ~(1 << PORTB5);

		// --- LECTURA ADC ---
		ADCSRA |= (1 << ADSC);
		dec_hex(contadorADC);

		// --- MULTIPLEXADO CON LIMPIEZA ---

		// PASO 1: (APAGADO TOTAL)
		PORTD &= ~((0 << PORTD0) | (0 << PORTD1));
		PORTC &= ~0x3F;
		PORTD &= ~(0 << PORTD2);
		_delay_us(500);

		// PASO 2: MOSTRAR UNIDADES
		setSegments(LowNibble);                    // Cargar patrón
		PORTD |= (1 << PORTD0);                    // Activar transistor Unidades
		_delay_ms(200);

		// PASO 3: (APAGADO TOTAL)
		PORTD &= ~((0 << PORTD0) | (0 << PORTD1));
		PORTC &= ~0x3F;
		PORTD &= ~(0 << PORTD2);
		_delay_us(500);

		// PASO 4: MOSTRAR DECENAS
		setSegments(HighNibble);                   // Cargar patrón
		PORTD |= (1 << PORTD1);                    // Activar transistor Decenas
		_delay_ms(200);
	}
}

void dec_hex(uint8_t val) {
	HighNibble = (val >> 4) & 0x0F;
	LowNibble = val & 0x0F;
}

void initADC(void) {
	ADMUX = (1 << REFS0) | (1 << ADLAR) | 0x07;
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void setSegments(uint8_t nibble) {
	uint8_t pattern = hexaDisplay[nibble];
	
	// Solo modificamos los pines del display (A0-A5)
	PORTC = (PORTC & ~0x3F) | (pattern & 0x3F);
	
	// Segmento G en D2
	if (pattern & (1 << 6)) PORTD |= (1 << PORTD2);
	else PORTD &= ~(1 << PORTD2);
}

// --- INTERRUPCIONES ---
ISR(ADC_vect) {
	contadorADC = ADCH;
}

ISR(PCINT2_vect) {
	static uint8_t flag3 = 0;
	static uint8_t flag4 = 0;

	// Incrementar (D3)
	if (!(PIND & (1 << PIND3))) {
		if (flag3 == 0) { contador++; flag3 = 1; }
		} else { flag3 = 0; }

		// Decrementar (D4)
		if (!(PIND & (1 << PIND4))) {
			if (flag4 == 0) { contador--; flag4 = 1; }
			} else { flag4 = 0; }
		}