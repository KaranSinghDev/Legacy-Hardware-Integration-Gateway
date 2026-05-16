// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Karan Singh
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Affero General Public License for more details.
//
// You should have received a copy of the License along with this
// program. If not, see <https://www.gnu.org/licenses/>.

#include "lhig/legacy_client.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace lhig {

LegacyClient::LegacyClient(const std::string &host, int port)
    : host_(host), port_(port), sock_fd_(-1), is_connected_(false) {
  std::cout << "LegacyClient created for " << host_ << ":" << port_
            << std::endl;
}

LegacyClient::~LegacyClient() { disconnect(); }

// NEW: Implementation of the state checker
bool LegacyClient::isConnected() const { return is_connected_; }

bool LegacyClient::connect() {
  if (is_connected_)
    return true;

  const struct hostent *server = gethostbyname(host_.c_str());
  if (server == NULL) {
    std::cerr << "[Client] ERROR, no such host: " << host_ << std::endl;
    return false;
  }

  sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd_ < 0) {
    std::cerr << "[Client] Error creating socket" << std::endl;
    return false;
  }

  struct sockaddr_in serv_addr;
  std::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port_);

  if (::connect(sock_fd_, reinterpret_cast<struct sockaddr *>(&serv_addr),
                sizeof(serv_addr)) < 0) {
    // Suppress error spam here, the main loop will handle the retry logic
    close(sock_fd_);
    sock_fd_ = -1;
    return false;
  }

  std::cout << "[Client] Connected to " << host_ << ":" << port_ << std::endl;
  is_connected_ = true;
  return true;
}

void LegacyClient::disconnect() {
  if (is_connected_ && sock_fd_ >= 0) {
    close(sock_fd_);
    is_connected_ = false;
    sock_fd_ = -1;
    std::cout << "[Client] Disconnected." << std::endl;
  }
}

std::string LegacyClient::sendCommand(const std::string &command) {
  if (!is_connected_) {
    return "ERR:NOT_CONNECTED";
  }

  std::string payload = command + "\n";

  // CRITICAL FIX: If send fails, force disconnect
  if (send(sock_fd_, payload.c_str(), payload.length(), MSG_NOSIGNAL) < 0) {
    disconnect();
    return "ERR:DISCONNECTED";
  }

  char buffer[1024] = {0};
  // CRITICAL FIX: <= 0 means peer closed connection or network error
  if (read(sock_fd_, buffer, 1024) <= 0) {
    disconnect();
    return "ERR:DISCONNECTED";
  }

  std::string response(buffer);
  if (!response.empty() && response.back() == '\n') {
    response.pop_back();
  }
  return response;
}

} // namespace lhig
