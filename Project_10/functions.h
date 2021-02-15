//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);
void Init_Timer_B0(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);
void Init_Chars(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void Timer1_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter

// Clocks
void Init_Clocks(void);
void clock_process(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);
void clear_LCD(void);


void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(int configure);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

void runSwitches(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

void stop(int nCycles);

//Shapes
void runShapes(void);
void displayShapes(void);
void drawCW_Circle(void);
void drawCCW_Circle(void);
void drawTriangle(void);
void drawFigureEight(void);
void drawFigureEightTwo(void);
void drawFigureEightThree(void);
void drawFigureEightFinish(void);
void turnRightEight(void);
void turnLeftEight(void);
void triangleLeg(void);
void trianglePoint(void);

//Wheels

void stop_Movement(void);
void move_Forward(void);
void move_Reverse(void);
void spin_CW(void);
void spin_CCW(void);
void turn_CW(void);
void pause(int numSeconds);
void Init_Wheels(void);
void wheel_control(void);

//ADC
void HEXtoBCD(int hex_value);
void adc_line4(int position);
void adc_line2(int position);
void adc_line3(int position);
void Init_ADC(void);
void emitter_Off(void);
void emitter_On(void);
void clear_adc_char(void);

// Serial communication
void out_character(char character);
void out_string(char *str);
void Serial_Display_Process(void);
void Send_And_Receive(void);


/* not used
void turnOnRight(void);
void turnOnLeft(void);
void turnOffRight(void);
void turnOffLeft(void);
void rightTurn(void);
void leftTurn(void);
void straightLine(void);
void sharpTurnRight(void);
void sharpTurnLeft(void);
void setRightSpeed(int speed);
void setLeftSpeed(int speed);
void resetMotors(void);*/

void clear_receive_char(void);
void clear_transmit_char(void);
void clear_command_buf(void);

//display functions
void clear_line4(void);
void clear_line2(void);
void clear_line1(void);
void clear_line3(void);

// menu functions
void menu_process(void);
void Resistor_Menu_Process(void);
void Resistor_Scroll(void);
void Shapes_Menu_Process(void);
void Shapes_Scroll(void);
void main_menu(void);
void Song_Scroll(void);

// IOT functions
void process_command(void);
void reset_USB_Char_Rx(void);
void reset_process_buf(void);
void wait_for_command(void);
void copy_to_transmit(void);

void get_ip(void);
void display_ip(void);
void process_ip(void);
void send_command(char command[]);

void verify_command(void);
void get_command_time(void);
void clear_transmit_command(void);

void getCurrentState(void);
void turn_Right(void);
void turn_Left(void);
void LineFollowing(void);
void inch_Forward(void);
void searchForLine(void);
void wait_ntime(int);
void correct_Line(void);
void display_ADC(void);
void getCircleTime(int hex_value);
void display_timer(void);
void exit_loop(void);
void main_display_process(void);
void forward_ntime(int);
void CW_ntime(int);

void CCW_ntime(int);

void calibrate_sensors(void);
void PID_LineFollowing(void);
int SimplePID(void);
void PID_WheelControl(int control);
void ReadADC(void);









