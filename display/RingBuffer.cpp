/*
 * RingBuffer.h
 *
 *  Created on: Jun 10, 2010
 *      Author: justin
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <inttypes.h>

/**
 * This is a uc-friendly ring buffer template. Most of
 * the time memory is pre-allocated on a u-controller so allowing the
 * caller to pass in a buffer and it's size (in elements) makes this
 * code much more reusable.
 */

template <typename T>
class RingBuffer {
  public:
	/**
	 * Be sure and pass in the size in number of elements NOT size in bytes.
	 */
	RingBuffer(T* buffer, uint8_t sizeInElements);

    T popFront();
    bool pushBack(T);
    bool isFull();
    bool hasData();

  private:
    T* buf;
    uint8_t bufSize;
    uint8_t head, tail;
};

template<typename T>
RingBuffer<T>::RingBuffer(T* bufferPtr, uint8_t sizeInElements) {
	buf = bufferPtr;
	bufSize = sizeInElements;
	head = 0;
	tail = 0;
}

template<typename T>
inline bool RingBuffer<T>::isFull() {
	return ((tail+1)%bufSize) == head;
}

template<typename T>
inline bool RingBuffer<T>::hasData() {
	return !(head == tail);
}

template<typename T>
T RingBuffer<T>::popFront() {
	if (hasData()) {
		T data = buf[head];
		head = (head+1) % bufSize;
		return data;
	}

	return NULL;
}

template<typename T>
bool RingBuffer<T>::pushBack(T data) {
	if (!isFull()) {
		buf[tail] = data;
		tail = (tail+1) % bufSize;
		return true;
	}

	return false;
}

#endif /* RINGBUFFER_H_ */

