#ifndef UPDATEABLE_H
#define UPDATEABLE_H


class Updateable
{
    public:
        Updateable();
        virtual ~Updateable();
        virtual void update() = 0;
    protected:
    private:
};

#endif // UPDATEABLE_H
