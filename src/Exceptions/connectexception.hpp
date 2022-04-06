// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2022 Πέτρος Σιλιγκούνας <petross404@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CONNECTEXCEPTION_H
#define CONNECTEXCEPTION_H

#include <stdexcept>
#include <exception>
#include <string>

class ConnectException : std::exception
{

public:
	ConnectException() = default;
	explicit ConnectException(const char* msg);

	const char* what() const throw() override;

private:
	std::string m_msg;
};

#endif // CONNECTEXCEPTION_H
