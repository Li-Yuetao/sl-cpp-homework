#include <iostream>
#include <vector>

int main()
{
    constexpr size_t buffer_count = 10001;
    std::vector<size_t> buffer(buffer_count);
    for(size_t i = 0; i < buffer_count; ++i)
    {
        buffer[i] = i;
    }

    // get max value of buffer
    size_t max_value = buffer[0];
    auto ptr = buffer.begin();
    size_t i = 0;
    switch (buffer_count % 8)
        for(; i < (buffer_count + 7) / 8; ++i)
        {
            [[fallthrough]];
            case 0: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]];
            case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
        }
    std::cout << "max value: " << max_value << std::endl;
}
