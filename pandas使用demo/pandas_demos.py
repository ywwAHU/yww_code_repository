#####

# from inspect import formatannotationrelativeto

import pandas as pd
def readme():
    """
    简单描述
    1. pandas读csv,将其分割为三份,存为csv
    2. 对DataFrame 数据做判断                     生成csv时可以设置index=False
    
    """
    print("简单描述")


def split_data(file):
    file_path = file 
    data = pd.read_csv(file_path)
    value = data.values
    train = value[1]
    test = value[0]
    validation = value[8]
    for index in range(2,value.shape[0]):
        if index % 16 == 0:
            
            test.append(value[index])
        elif index % 8 == 0:
            validation.append(value[index])
        else:
            train.append(value[index])

    df_train = pd.DataFrame(train)
    df_test = pd.DataFrame(test)
    df_validation = pd.DataFrame(validation)

    df_train.to_csv("C:/Users/HD/Desktop/污水厂/实验测试/0326实验/数据集/train.csv")
    df_test.to_csv("C:/Users/HD/Desktop/污水厂/实验测试/0326实验/数据集/test.csv")
    df_validation.to_csv("C:/Users/HD/Desktop/污水厂/实验测试/0326实验/数据集/validation.csv")


def delete_dataFrame(file_path):
    data = pd.read_csv(file_path)
    data = data[(data['1']!=-1)]
    df = pd.DataFrame(data)
    df.to_csv("",index= False)



