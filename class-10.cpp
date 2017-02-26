/*
Drew Gilbertson
Project 10
Section 7
* 
* This program does various tasks to a TextBuffer class, which is 
* essentially a line of text. 
* 
 */ 


#include<iostream>
using std::ostream;
#include<algorithm>
using std::swap;
#include<iterator>
using std::ostream_iterator;

#include "class-10.h"
//all of the constructors, gives default values, defaults to 10
TextBuffer::TextBuffer(size_t s){
	buf_ = new char[s];
	size_=0;
	cursor_ = 0;
	back_=s-1;
	capacity_=s;
}
//constructor with an object passed in
TextBuffer::TextBuffer(TextBuffer& a){
			this->cursor_=a.cursor_;
			this->capacity_ = a.capacity_;
			this->size_ = a.size_;
			this->buf_ = new char[a.capacity_];
			std::copy(a.buf_, a.buf_ + a.size_, this->buf_);
}
//returns an object that is created equal
TextBuffer& TextBuffer::operator =(TextBuffer a){
			this->cursor_=a.cursor_;
			this->capacity_ = a.capacity_;
			this->size_ = a.size_;
			this->buf_ = new char[a.capacity_];
			std::copy(a.buf_, a.buf_ + a.size_, this->buf_);
			std::swap(this->buf_,a.buf_);
			return *this;
}
//swaps all parts of a TextBuffer object with another
void TextBuffer::swap(TextBuffer& a){
	std::swap(a.buf_,this->buf_);
	std::swap(a.size_,this->size_);
	std::swap(a.capacity_,this->capacity_);
	std::swap(a.back_,this->back_);
	std::swap(a.cursor_,this->cursor_);

	
}
//destructor, deletes the array
TextBuffer::~TextBuffer(){
	delete [] buf_;
}
//insert, main feature. inserts a char at the cursor, and moves it
//will grow the array if there is no room
void TextBuffer::insert(char c){
	if(!this->isfull()){
		buf_[cursor_++]=c;
		size_++;
		
	}
	else{
		//growing array then adding at cursor
		this->grow();
		buf_[cursor_++]=c;
		size_++;
	}
}
//doubles size of buffer if called
void TextBuffer::grow(){
	char* new_buf = new char[capacity_*2];
	std::copy(buf_,buf_+cursor_,new_buf);
	std::copy(buf_+(cursor_+1),buf_+capacity_,new_buf+cursor_+capacity_+1);
	std::swap(buf_,new_buf);
	delete [] new_buf;
	//assigning new values
	back_+=capacity_;
	capacity_*=2;
}
//checking to see if buffer is empty
bool TextBuffer::isempty(){
	if (size_==0)
		return true;
	else
		return false;
}

//checks to see if the buffer is full
bool TextBuffer::isfull(){
	if(size_==capacity_-1)
		return true;
	else
		return false;
	}
//moves the cursor to the left, adds the character to the end
bool TextBuffer::left(){
	if(cursor_==0)
		return false;
	else {
		buf_[back_]=buf_[--cursor_];
		back_--;
		return true;
	}
}
//moves cursor to right, brings character back to point	
bool TextBuffer::right(){
	if (cursor_!=capacity_){
		buf_[cursor_]=buf_[++back_];
		cursor_++;
		return true;
	}
	else
		return false;
}

//deletes a letter, reduces size to 1
bool TextBuffer::del(){
	if(cursor_==0)
		return false;
	else{
	cursor_--;
	size_--;
	return true;
}
}
//prints out the objecct using an output stream
ostream& operator<<(ostream &out, TextBuffer &tb){
	out<<"size: "<<tb.size_<<" capacity:"<<tb.capacity_<<" cursor:"
	<<tb.cursor_<<" back: "<<tb.back_<<std::endl;
    std::copy(tb.buf_, (tb.buf_+tb.capacity_), 
    ostream_iterator<char>(out, ","));
    out<<std::endl;
    std::copy(tb.buf_, tb.buf_+tb.cursor_,ostream_iterator<char>(out));
    out<<"|";
	std::copy(tb.buf_+tb.back_+1,tb.buf_+tb.capacity_,
	ostream_iterator<char>(out));
    return out;
}
