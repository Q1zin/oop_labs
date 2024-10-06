#include "BitArray.h"

static constexpr int BITS_PER_LONG = sizeof(unsigned long) * 8;

BitArray::BitArray() : num_bits(0) {}
BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) {  
    if (num_bits < 0) 
        throw std::invalid_argument("Size must be non-negative"); 

    this->num_bits = num_bits;
    data.resize((num_bits + BITS_PER_LONG - 1) / BITS_PER_LONG, 0);
    if (num_bits > 0 && !data.empty())
        data[0] = value;
}

BitArray::BitArray(const BitArray& b) {
    this->num_bits = b.num_bits;
    this->data = b.data;
}

void BitArray::swap(BitArray &b) {
    std::swap(this->num_bits, b.num_bits);
    std::swap(this->data, b.data);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        num_bits = b.num_bits;
        data = b.data;
    }

    return *this;
}

void BitArray::resize(int new_size, bool value) {
    if (new_size < 0) 
        throw std::invalid_argument("New size must be non-negative"); 

    int new_data_size = (new_size + BITS_PER_LONG - 1) / BITS_PER_LONG; 

    if (new_size < num_bits) { 
        data.resize(new_data_size); 
        if (new_size % BITS_PER_LONG != 0) 
            data.back() &= (1UL << (new_size % BITS_PER_LONG)) - 1; 
    } else if (new_size > num_bits) {  
        data.resize(new_data_size, value ? ~0UL : 0UL);  

        if (num_bits % BITS_PER_LONG != 0 && value)
            data[data.size() - 1] |= (~0UL << (num_bits % BITS_PER_LONG));

        if (new_size % BITS_PER_LONG != 0)  
            data.back() &= (1UL << (new_size % BITS_PER_LONG)) - 1;  
    }

    num_bits = new_size;
}

void BitArray::push_back(bool bit) {
    resize(num_bits + 1);
    set(num_bits - 1, bit);
}

void BitArray::clear() {
    num_bits = 0;
    data.clear();
}

BitArray& BitArray::set(int n, bool val) { 
    if (n >= num_bits) 
        throw std::out_of_range("Bit index out of range"); 

    if (val) 
        data[n / BITS_PER_LONG] |= (1UL << (n % BITS_PER_LONG)); 
    else  
        data[n / BITS_PER_LONG] &= ~(1UL << (n % BITS_PER_LONG)); 

    return *this; 
};

BitArray& BitArray::set() { 
    for (auto& block : data) 
        block = -1; 

    data[num_bits / BITS_PER_LONG] >>= BITS_PER_LONG - (num_bits % BITS_PER_LONG); 

    return *this; 
};


BitArray& BitArray::reset(int n) {
    if (n >= num_bits)
        throw std::out_of_range("Bit index out of range");

    data[n / BITS_PER_LONG] &= ~(1UL << (n % BITS_PER_LONG));

    return *this;
};

BitArray& BitArray::reset() {
    for (auto& block : data)
        block = 0;

    return *this;
};

bool BitArray::any() const {
    for (const auto& block : data)
        if (block != 0)
            return true;

    return false;
}

bool BitArray::none() const {
    return !any();
}

bool BitArray::operator[](int i) const {
    return data[i / BITS_PER_LONG] & (1UL << (i % BITS_PER_LONG));
}

BitArray BitArray::operator~() const { 
    BitArray result = *this;

    for (int i = 0; i < num_bits; i++)
        if (data[i / BITS_PER_LONG] & (1UL << (i % BITS_PER_LONG)))
            result.reset(i);
        else
            result.set(i);

    return result;
}

int BitArray::count() const {
    int count = 0;
    for (const auto block : data)
        for (int i = 0; i < BITS_PER_LONG; i++)
            if (block & (1UL << i))
                count++;

    return count;
}

int BitArray::size() const {
    return num_bits;
}

bool BitArray::empty() const {
    return num_bits == 0;
}

std::string BitArray::to_string() const {
    std::string str;
    for (int i = num_bits - 1; i >= 0; i--) {
        str += (*this)[i] ? '1' : '0';
    }

    return str;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (num_bits != b.num_bits)
        throw std::invalid_argument("Bit arrays must be of the same size for bitwise operations");

    int size = num_bits / BITS_PER_LONG;
    for (size_t i = 0; i <= size; i++)
        data[i] &= b.data[i];

    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (num_bits != b.num_bits)
        throw std::invalid_argument("Bit arrays must be of the same size for bitwise operations");

    int size = num_bits / BITS_PER_LONG;
    for (size_t i = 0; i <= size; i++)
        data[i] |= b.data[i];

    return *this;
}


BitArray& BitArray::operator^=(const BitArray& b) {
    if (num_bits != b.num_bits)
        throw std::invalid_argument("Bit arrays must be of the same size for bitwise operations");

    int size = num_bits / BITS_PER_LONG;
    for (size_t i = 0; i <= size; i++)
        data[i] ^= b.data[i];

    return *this;
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray new_bit_array(b1);
    new_bit_array &= b2;
    return new_bit_array;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray new_bit_array(b1);
    new_bit_array |= b2;
    return new_bit_array;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray new_bit_array(b1);
    new_bit_array ^= b2;
    return new_bit_array;
}

bool operator==(const BitArray& a, const BitArray& b) {
    return (a.num_bits == b.num_bits) && (a.data == b.data);
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0)
        throw std::invalid_argument("Shift amount must be non-negative");

    if (n >= num_bits) {
        reset();
        return *this;
    }

    unsigned long mask = (1UL << n) - 1;
    mask <<= BITS_PER_LONG - n;
    unsigned long transp_bits1 = (mask & data[0]) >> (BITS_PER_LONG - n);
    data[0] <<= n;

    int size = data.size();
    for (int i = 1; i < size; i++) {
        unsigned long transp_bits2 = (mask & data[i]) >> (BITS_PER_LONG - n);
        data[i] <<= n;
        data[i] |= transp_bits1;

        transp_bits1 = transp_bits2;
    }

    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0)
        throw std::invalid_argument("Shift amount must be non-negative");

    if (n >= num_bits) {
        reset();
        return *this;
    }

    unsigned long mask = (1UL << n) - 1;
    data[0] >>= n;

    int size = data.size();
    for (int i = 1; i < size; i++) {
        unsigned long transp_bits1 = (mask & data[i]) << (BITS_PER_LONG - n);
        data[i-1] |= transp_bits1;
        data[i] >>= n;
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray new_bit_array(*this);
    return new_bit_array <<= n;
}


BitArray BitArray::operator>>(int n) const {
    BitArray new_bit_array(*this);
    return new_bit_array >>= n;
}
