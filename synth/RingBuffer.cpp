/** @file RingBuffer.h
 *  @date Jun 10, 2010
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <inttypes.h>

/**
 * This is a uc-friendly ring buffer template class.
 *
 * Most of the time memory is pre-allocated on a u-controller so allowing the
 * caller to pass in a buffer and it's size (in elements) makes this
 * code more reusable in this context.
 *
 * @author Justin May <may.justin@gmail.com>
 */
template <typename T>
class RingBuffer {

public:
    /**
     * Create a new ring buffer that is wrapped around a previous allocated chunk of ram.
     *
     * @param buffer            Pointer to an array in ram
     * @param sizeInElements    The size of the array, measured in number of elements.
     *
     * @warning Be sure and pass in the size in number of elements NOT size in bytes.
     */
    RingBuffer( T* buffer, uint8_t sizeInElements );

    /**
     * Retrieve the head element and remove it from the buffer.
     *
     * @return Value at the head of the buffer
     */
    T get();

    /**
     * Push an element into the buffer
     *
     * @param element   Value to be pushed into the buffer.
     * @return True if the element could be placed on the list, false if the buffer is full.
     */
    bool push(T element);

    /**
     * Check if the buffer is full
     *
     * @return True if the buffer is full, false if there is still room left
     */
    bool isFull();

    /**
     * Check and see if the buffer has data ready in it
     *
     * @return True if there is data to be retrieved in the buffer, false if not
     */
    bool hasData();

    /**
     * Clear the buffer contents
     */
    void flush();

private:
    /// Pointer to the slice of memory containing the ring buffer data
    T* _buf;

    /// Size of _buf (in number of elements)
    uint8_t _bufSize;
   
    /// Index of the head of the ring buffer
    uint8_t _head;

    /// Index of the tail of the ring buffer
    uint8_t _tail;
};

template<typename T>
RingBuffer<T>::RingBuffer( T* bufferPtr, uint8_t sizeInElements ) {
    _buf = bufferPtr;
    _bufSize = sizeInElements;
    _head = 0;
    _tail = 0;
}

template<typename T>
inline bool RingBuffer<T>::isFull() {
    return ( ( _tail + 1 ) % _bufSize) == _head;
}

template<typename T>
inline bool RingBuffer<T>::hasData() {
    return !( _head == _tail );
}

template<typename T>
inline void RingBuffer<T>::flush() {
    _head = _tail = 0;
}

template<typename T>
T RingBuffer<T>::get() {
    if ( hasData() ) {
        T data = _buf[ _head ];
        _head = ( _head + 1 ) % _bufSize;
        return data;
    }

    return 0;
}

template<typename T>
bool RingBuffer<T>::push(T data) {
    if (!isFull()) {
        _buf[ _tail ] = data;
        _tail = ( _tail + 1 ) % _bufSize;
        return true;
    }

    return false;
}

#endif /* RINGBUFFER_H_ */

