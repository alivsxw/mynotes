
typedef struct binary_search_tree{
    struct binary_search_tree* left;//左孩子
    struct binary_search_tree* right;//右孩子
    struct binary_search_tree* parent;//父节点
    int value;//数据，可以引申为结构体，但需要提供不同的算法
}binary_search_tree;
/**
typedef struct operation_binary_search{
    binary_search_tree* (*binary_search_tree_create)(binary_search_tree* T,int* value_array,int array_length,struct operation_binary_search*operation);//创建
    binary_search_tree* (*binary_search_tree_insert)(binary_search_tree* T,int key);//插入
    void (*print_binary_tree_value)(binary_search_tree*T);//遍历
}operation_binary_search;
**/
#define LEFT(T) T->left //左子树
#define RIGHT(T) T->right //右子树
#define PARENT(T) T->parent //父节点

binary_search_tree* binary_search_tree_insert(binary_search_tree* T,int key){
    if(T == NULL){//找到位置，即为NULL，根据递归的性质，返回值T会自动链接到上一层，上一层的函数中有对T->left和T->right赋值。
        T = (binary_search_tree*)malloc(sizeof(binary_search_tree));
        T ->value = key;
        T ->right = T ->left = T ->parent = NULL;
    }else{
        if(T ->value > key) {
                T ->left = binary_search_tree_insert(T->left,key);//沿着左子树向下找
                T ->left ->parent = T;
        }
        else {
                T ->right = binary_search_tree_insert(T->right,key);//沿着右子树向下找
                T ->right ->parent = T;
        }
    }
    return T;
}
//以T为根的树的最小值
binary_search_tree* MIN_binary_search_tree_value(binary_search_tree* T){
    while(LEFT(T) != NULL){
        T = LEFT(T);
    }
    return T;
}
binary_search_tree* search_key_from_binary_search_tree(binary_search_tree* T,int key){
    binary_search_tree* temp = T;
    while(temp != NULL && temp->value != key){
        if(key < temp ->value) temp = temp ->left;
        else temp = temp ->right;
    }
    return temp;
}
binary_search_tree * binary_search_tree_create(binary_search_tree* T,int* value_array,int array_length)
{
    for(int i = 0;i < array_length;i++){
        T = binary_search_tree_insert(T,value_array[i]);
    }
    return T;
}
void print_binary_tree_value(binary_search_tree* T){
if(T != NULL){
print_binary_tree_value(T->left);
printf(" %d;",T -> value);
print_binary_tree_value(T ->right);
}
}

//查找后继节点
binary_search_tree* next_node_binary_search_tree_inorder(binary_search_tree* T)
{
    binary_search_tree* result,* pre = PARENT(T);
    if(RIGHT(T) != NULL)
	{
        result = MIN_binary_search_tree_value(RIGHT(T));//右子树的最小值所在的结点的指针
    }
	else
	{
        while(pre!=NULL && pre == RIGHT(T))
		{//沿着右子树向下走，pre初始值为T的父节点
            T = pre;
            pre = PARENT(T);
        }
        //跳出后，pre或者为空，或者是查找到的后继
        result = pre;
    }
    return result;
}

//删除算法
binary_search_tree* delete_key_node_pointer(binary_search_tree* T,binary_search_tree* key_node){
    binary_search_tree* delete_node = NULL;
    binary_search_tree* delete_node_son = NULL;
    if(LEFT(key_node) == NULL || RIGHT(key_node) == NULL)
	{
        delete_node = key_node;
    }
	else
	{
        delete_node = next_node_binary_search_tree_inorder(key_node);//将应该删除的节点置为原节点的后继结点
    }
	
    if(LEFT(delete_node) != NULL) 
		delete_node_son = LEFT(delete_node);//左孩子
    else 
		delete_node_son = RIGHT(delete_node);//右孩子或者空
		
    if(delete_node_son != NULL) 
		PARENT(delete_node_son) = PARENT(delete_node);
	
    if(PARENT(delete_node) == NULL)//删除的是根节点
	{
        T = delete_node_son;
    }
	else
	{
        //将被删除节点的孩子节点链接到其父节点上，判断应该链接到哪棵子树上
        if(LEFT(PARENT(delete_node)) == delete_node) 
			LEFT(PARENT(delete_node)) = delete_node_son;
        else 
			RIGHT(PARENT(delete_node)) = delete_node_son;
    }
    if(delete_node != key_node) 
		key_node -> value = delete_node -> value;
    free(delete_node);
    return T;
}
//做一些简单的安全操作，调用delete_key_node_pointer
binary_search_tree* delete_key_node_key_value(binary_search_tree* T,int key){
    binary_search_tree* key_node = search_key_from_binary_search_tree(T,key);
    if(key_node == NULL||T == NULL){
        printf("ERROR!");
        return NULL;
    }else{
        return delete_key_node_pointer(T,key_node);
    }
}

int main()
{
	int data[5] = {1,2,3,4,5};
	int array_length = 5;
	binary_search_tree* T = NULL;
	T = binary_search_tree_create(T,data,array_length);
	print_binary_tree_value(T);
	printf("\n");

	T = delete_key_node_key_value(T,1);
	print_binary_tree_value(T);
	printf("\n");

	T = delete_key_node_key_value(T,2);
	print_binary_tree_value(T);
	printf("\n");

	T = delete_key_node_key_value(T,3);
	print_binary_tree_value(T);
	printf("\n");

	T = delete_key_node_key_value(T,4);
	print_binary_tree_value(T);
	printf("\n");

	T = delete_key_node_key_value(T,5);
	print_binary_tree_value(T);
	printf("\n");
	
	return 0;
}


/**

//查找节点
CORED_TREE_NODE_S* CORED_TREE_SearchCard(CORED_TREE_NODE_S* T,CORED_CARD_DB_S *pstCard)
{
    CORED_TREE_NODE_S* temp = T;

	int card = 0;
	int word = 0;
	int len = 0;
	int ifword = 0;
	int ifcard = 0;
	len = strlen(pstCard->cWorkid);
	if(len > 0)
	{
		ifword = 1;
	}

	len = strlen(pstCard->cCard);
	if(len > 0)
	{
		ifcard = 1;
	}

	printf("\033[1m\033[40;32m	SearchCard  cCard:%s;cWorkid:%s[%s:%d]\033[0m\n",pstCard->cCard,pstCard->cWorkid, __func__, __LINE__);
	
	while(NULL != temp)
	{
		printf("\033[1m\033[40;32m	SearchCard  db:%s;ser:%s[%s:%d]\033[0m\n",temp->stCard.cCard,pstCard->cCard, __func__, __LINE__);
		card = strcmp(temp->stCard.cCard,pstCard->cCard); //k>0  参数1 > 参数2
		
		if(0 == card)
		{	
			if(ifword)
			{
				word = strcmp(temp->stCard.cWorkid,pstCard->cWorkid);
				if(0 == word)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		
		if(card > 0) 
			temp = temp->left;
        else 
			temp = temp->right;
    }
	
	#if 0
    while((temp != NULL) && (temp->value != key))
	{
		printf("\033[1m\033[40;32m	temp->value:%d;key:%d  [%s:%d]\033[0m\n",temp->value,key, __func__, __LINE__);
	
        if(key < temp->value) 
			temp = temp->left;
        else 
			temp = temp->right;
    }
    #endif

	//printf("\033[1m\033[40;32m	SearchCard temp:%p  [%s:%d]\033[0m\n",temp, __func__, __LINE__);
	
    return temp;
}


**/