/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   debug_config.h
 * Author: roseba
 *
 * Created on February 5, 2022, 12:05 PM
 */

#pragma once

#include <stdio.h>
#include <iostream>

class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};

#ifdef DEBUG
#define log_i  std::cout
#define log_line  std::cout <<  __FILE__ <<  std::endl
#define log_func  std::cout <<  __PRETTY_FUNCTION__ << std::endl
#else
static NullBuffer null_buffer;
static std::ostream null_stream(&null_buffer);
#define log_i null_stream
#define log_func
#define log_line
#endif

