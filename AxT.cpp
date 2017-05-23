

struct Way{
    Letter *
}

struct Letter{
    Way *waysTo;

    Letter(Way* arr){
        waysTo = arr;
    }
    ~Letter(){
        delete [] waysTo;
    }
}


