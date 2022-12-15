/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:13 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/20 12:12:34 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*Keys*/
# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2
# define MOUSE_THIRD_BUTTON	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define MOUSE_SCROLL_LEFT	6
# define MOUSE_SCROLL_RIGHT	7

# define ARROW_LEFT			123
# define ARROW_RIGHT		124
# define ARROW_DOWN			125
# define ARROW_UP			126

# define NUM_PAD_0			82
# define NUM_PAD_1			83
# define NUM_PAD_2			84
# define NUM_PAD_3			85
# define NUM_PAD_4			86
# define NUM_PAD_5			87
# define NUM_PAD_6			88
# define NUM_PAD_7			89
# define NUM_PAD_8			91
# define NUM_PAD_9			92
# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_Q			12
# define MAIN_PAD_M			46
# define MAIN_PAD_C			8
# define MAIN_PAD_0			29
# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_5			23
# define MAIN_PAD_6			22
# define MAIN_PAD_7			26
# define MAIN_PAD_8			28
# define MAIN_PAD_9			25
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27
# define MAIN_PAD_LESS		43
# define MAIN_PAD_MORE		47

/*Events and Masks*/
# define KEY_PRESS			2
# define KEY_RELEASE		3
# define MOUSE_PRESS		4
# define MOUSE_RELEASE		5
# define MOUSE_MOVE			6
# define DESTROY			17

# define KEYPRESS_MASK		1
# define KEYRELEASE_MASK	2
# define MOUSEPRESS_MASK	4
# define MOUSERELEASE_MASK	8
# define LEAVEWINDOW_MASK	32
# define MOUSEMOVE_MASK		64
# define NO_MASK			0

#endif	/*keys.h*/
