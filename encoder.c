/*
 * encoder.c
 *
 *  Created on: Aug 17, 2022
 *      Author: MSZ
 */



/**
 * Copyright (c) 2022 MSZ98

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */



/**    A1 A2 B1 B2 ?
 * 0   0  0  0  0  nothing
 * 1   0  0  0  1  backward
 * 2   0  0  1  0  forward
 * 3   0  0  1  1  nothing
 * 4   0  1  0  0  forward
 * 5   0  1  0  1  forward 2x
 * 6   0  1  1  0  backward 2x
 * 7   0  1  1  1  backward
 * 8   1  0  0  0  backward
 * 9   1  0  0  1  backward 2x
 * 10  1  0  1  0  forward 2x
 * 11  1  0  1  1  forward
 * 12  1  1  0  0  nothing
 * 13  1  1  0  1  forward
 * 14  1  1  1  0  backward
 * 15  1  1  1  1  nothing
 *
 * forward:    {2, 4, 11, 13}
 * backward:   {1, 7, 8, 14}
 * forward2x:  {6, 9}
 * backward2x: {5, 10}
 * */



void Encoder_loop(int *v) {

	// int A2 = HAL_GPIO_ReadPin(Encoder_A_GPIO_Port, Encoder_A_Pin);
	// int B2 = HAL_GPIO_ReadPin(Encoder_B_GPIO_Port, Encoder_B_Pin);
	int A2 = digitalRead(Encoder_A_Pin);
	int B2 = digitalRead(Encoder_B_Pin);

	static int X;
	X <<= 1;
	X &= 0xA;
	X |= A2 << 2 | B2;

	switch(X) {
	case 2:
	case 4:
	case 11:
	case 13:
		(*v)++;
		break;
	case 1:
	case 7:
	case 8:
	case 14:
		(*v)--;
		break;
	case 5:
	case 10:
		(*v) += 2;
		break;
	case 6:
	case 9:
		(*v) -= 2;
		break;
	}

}














