
#include <PCH.h>

static const int n = 8;
static const int size = 2 << n;

namespace QPP {
    class BraKet {
    public:
        BraKet();

        uint8_t getValueAt(int row);
        void setValueAt(int row, int value);

    private:
        std::array<uint8_t, size> data;
    };
}
