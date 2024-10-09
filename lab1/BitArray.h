#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>
#include <vector>

/**
 * @class BitArray
 * @brief A dynamic bit array for compact storage and manipulation of bits.
 *
 * The `BitArray` class provides an efficient way to store and manipulate
 * a collection of bits. It supports dynamic resizing, bitwise operations,
 * and other useful functionalities for working with binary data. This class
 * is memory-efficient, storing bits compactly in blocks of `unsigned long`.
 */
class BitArray {
private:
    int num_bits; ///< Number of bits in the array
    std::vector<unsigned long> data; ///< Storage for the bits in blocks of unsigned long

    /**
    * @brief Generates a bitmask with a single bit set at the specified index.
    *
    * @param[in] num_bits Index of the bit to be set in the mask.
    * @return A bitmask with the bit at the given index set to 1.
    */
    unsigned long getBitMask(int num_bits) const;

public:
    /**
     * @brief Default constructor. Initializes an empty BitArray.
     *
     * @throws std::bad_alloc if memory allocation fails.
     */
    BitArray();

    /**
     * @brief Destructor for the BitArray.
     */
    ~BitArray();

    /**
     * @brief Constructor that initializes the BitArray with a given size and initial value.
     *
     * @param[in] num_bits  Number of bits in the array.
     * @param[in] value     Initial value for the bits (default is 0).
     *
     * @throws std::bad_alloc if memory allocation fails.
     */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /**
     * @brief Copy constructor.
     *
     * @param[in] b BitArray to be copied.
     */
    BitArray(const BitArray& b);

    /**
     * @brief Swaps the contents of this BitArray with another.
     *
     * @param[in] b BitArray to swap with.
     */
    void swap(BitArray& b);

    /**
     * @brief Assignment operator for BitArray.
     *
     * @param[in] b BitArray to be assigned.
     * @return Reference to this BitArray.
     */
    BitArray& operator=(const BitArray& b);

    /**
     * @brief Resizes the BitArray to a new size.
     *
     * @param[in] new_size New size of the array.
     * @param[in] value    The bit value to initialize new elements (default is false).
     *
     * @throws std::invalid_argument if the new size is negative.
     */
    void resize(int new_size, bool value = false);

    /**
     * @brief Clears the BitArray, setting its size to zero.
     */
    void clear();

    /**
     * @brief Adds a bit to the end of the array.
     *
     * @param[in] bit The bit to be added.
     */
    void push_back(bool bit);

    /**
     * @brief Performs a bitwise AND operation with another BitArray.
     *
     * @param[in] b Another BitArray.
     * @return Reference to this BitArray after the operation.
     *
     * @throws std::invalid_argument if the BitArrays are of different sizes.
     */
    BitArray& operator&=(const BitArray& b);

    /**
     * @brief Performs a bitwise OR operation with another BitArray.
     *
     * @param[in] b Another BitArray.
     * @return Reference to this BitArray after the operation.
     *
     * @throws std::invalid_argument if the BitArrays are of different sizes.
     */
    BitArray& operator|=(const BitArray& b);

    /**
     * @brief Performs a bitwise XOR operation with another BitArray.
     *
     * @param[in] b Another BitArray.
     * @return Reference to this BitArray after the operation.
     *
     * @throws std::invalid_argument if the BitArrays are of different sizes.
     */
    BitArray& operator^=(const BitArray& b);

    /**
     * @brief Shifts the bits in this BitArray to the left by a specified number of positions.
     *
     * @param[in] n Number of positions to shift.
     * @return Reference to this BitArray after the shift.
     *
     * @throws std::invalid_argument if the shift amount is negative.
     */
    BitArray& operator<<=(int n);

    /**
     * @brief Shifts the bits in this BitArray to the right by a specified number of positions.
     *
     * @param[in] n Number of positions to shift.
     * @return Reference to this BitArray after the shift.
     *
     * @throws std::invalid_argument if the shift amount is negative.
     */
    BitArray& operator>>=(int n);

    /**
     * @brief Non-mutating bitwise left shift.
     *
     * @param[in] n Number of positions to shift.
     * @return A new BitArray with the bits shifted.
     */
    BitArray operator<<(int n) const;

    /**
     * @brief Non-mutating bitwise right shift.
     *
     * @param[in] n Number of positions to shift.
     * @return A new BitArray with the bits shifted.
     */
    BitArray operator>>(int n) const;

    /**
     * @brief Sets the bit at the given index.
     *
     * @param[in] n Index of the bit to set.
     * @param[in] val Boolean value to set (true for 1, false for 0).
     * @return Reference to this BitArray.
     *
     * @throws std::out_of_range if the index is out of bounds.
     */
    BitArray& set(int n, bool val = true);

    /**
     * @brief Sets all bits in the BitArray to 1.
     *
     * @return Reference to this BitArray.
     */
    BitArray& set();

    /**
     * @brief Clears the bit at the given index (sets it to 0).
     *
     * @param[in] n Index of the bit to clear.
     * @return Reference to this BitArray.
     *
     * @throws std::out_of_range if the index is out of bounds.
     */
    BitArray& reset(int n);

    /**
     * @brief Clears all bits in the BitArray (sets all to 0).
     *
     * @return Reference to this BitArray.
     */
    BitArray& reset();

    /**
     * @brief Checks if any bits are set to 1.
     *
     * @return True if any bits are set, otherwise false.
     */
    bool any() const;

    /**
     * @brief Checks if no bits are set (all are 0).
     *
     * @return True if no bits are set, otherwise false.
     */
    bool none() const;

    /**
     * @brief Inverts all bits in the BitArray.
     *
     * @return A new BitArray with all bits inverted.
     */
    BitArray operator~() const;

    /**
     * @brief Counts the number of bits set to 1.
     *
     * @return The number of set bits.
     */
    int count() const;

    /**
     * @brief Accesses the bit at the given index.
     *
     * @param[in] i Index of the bit.
     * @return The value of the bit (true or false).
     *
     * @throws std::out_of_range if the index is out of bounds.
     */
    bool operator[](int i) const;

    /**
     * @brief Returns the number of bits in the BitArray.
     *
     * @return The size of the BitArray.
     */
    int size() const;

    /**
     * @brief Checks if the BitArray is empty (contains no bits).
     *
     * @return True if empty, otherwise false.
     */
    bool empty() const;

    /**
    * @brief Convert the BitArray to a string representation.
    *
    * @return A string containing the bit representation (e.g., "101010").
    */
    std::string to_string() const;

    /**
    * @brief Compare two BitArrays for equality.
    *
    * @param[in] a The first BitArray.
    * @param[in] b The second BitArray.
    * @return True if the two arrays are equal, otherwise false.
    */
    friend bool operator==(const BitArray& a, const BitArray& b);

    /**
    * @brief Compare two BitArrays for inequality.
    *
    * @param[in] a The first BitArray.
    * @param[in] b The second BitArray.
    * @return True if the two arrays are not equal, otherwise false.
    */
    friend bool operator!=(const BitArray& a, const BitArray& b);

    /**
    * @brief Print all data blocks in the BitArray for debugging.
    *
    * @note This method is marked for future removal (`@todo`).
    */
    void printDataBit();
};

/**
* @brief Bitwise AND operation between two BitArrays.
*
* @param[in] b1 The first BitArray operand for the AND operation.
* @param[in] b2 The second BitArray operand for the AND operation.
* @return A new BitArray that contains the result of the AND operation.
*
* @throws std::invalid_argument if the two BitArrays have different sizes.
*/
BitArray operator&(const BitArray& b1, const BitArray& b2);

/**
* @brief Bitwise OR operation between two BitArrays.
*
* @param[in] b1 The first BitArray operand for the OR operation.
* @param[in] b2 The second BitArray operand for the OR operation.
* @return A new BitArray that contains the result of the OR operation.
*
* @throws std::invalid_argument if the two BitArrays have different sizes.
*/
BitArray operator|(const BitArray& b1, const BitArray& b2);

/**
* @brief Bitwise XOR operation between two BitArrays.
*
* @param[in] b1 The first BitArray operand for the XOR operation.
* @param[in] b2 The second BitArray operand for the XOR operation.
* @return A new BitArray that contains the result of the XOR operation.
*
* @throws std::invalid_argument if the two BitArrays have different sizes.
*/
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif // BITARRAY_H