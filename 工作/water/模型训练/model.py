############### 调参数

### 汇总

from matplotlib.pyplot import axis
from sklearn.multioutput import MultiOutputRegressor
import xgboost  as xgb
import  pandas  as  pd
from sklearn.metrics import r2_score
from sklearn.model_selection import train_test_split
import numpy as np


def train(train_x,train_y,test_x,test_y,params_list):
    xgb_train = xgb.DMatrix(train_x, label=train_y)
    xgb_test = xgb.DMatrix(test_x)


    # ====================================================

    # 训练： 建模


    params = {'booster': 'gbtree',
            'objective': 'reg:squarederror',  # 回归
            # 'gamma':0.1,  # 用于控制是否后剪枝的参数,越大越保守，一般0.1、0.2这样子。
            'max_depth': params_list['max_depth'],  # 构建树的深度，越大越容易过拟合 5
            # 'lambda':2,  # 控制模型复杂度的权重值的L2正则化项参数，参数越大，模型越不容易过拟合。
            'subsample': 0.7,  # 随机采样训练样本
            'colsample_bytree': 0.7,  # 生成树时进行的列采样
            'min_child_weight': 2,

            # 这个参数默认是 1，是每个叶子里面 h 的和至少是多少，对正负样本不均衡时的 0-1 分类而言
            # ，假设 h 在 0.01 附近，min_child_weight 为 1 意味着叶子节点中最少需要包含 100 个样本。
            # 这个参数非常影响结果，控制叶子节点中二阶导的和的最小值，该参数值越小，越容易 overfitting。
            'scale_pos_weight': 63,
            'silent': 0,  # 设置成1则没有运行信息输出，最好是设置为0. silent
            'eta': params_list['eta'],  # 如同学习率
            'nthread': 8, # cpu 线程数
            'eval_metric': 'rmse'  # 评价方式 ''linear logloss rmse
            }

    plst = list(params.items())
    num_rounds =params_list['num_rounds']  # 迭代次数
    watchlist = [(xgb_train, 'train')]
    # early_stopping_rounds    当设置的迭代次数较大时，early_stopping_rounds 可在一定的迭代次数内准确率没有提升就停止训练
    model = xgb.train(plst, xgb_train, num_rounds, watchlist)
    pred_value = model.predict(xgb_test)

    pred_value = pred_value

    num = 0
    num2 = 0
    num3 = 0.0
    tag_num = 0
    for i in range(len(test_y)):
        num = num + (abs(pred_value[i]-test_y[i]))**2
        num2 = num2 + (abs(pred_value[i]-test_y[i]))
        tag = ((abs(pred_value[i]-test_y[i]))/test_y[i])
        num3 = num3 +  tag
        
    target_list = ['cod','ss','nh3','tn','tp']

    print(len(test_y))
    print(target_list[target-16],',mse:',num/len(test_y))  
    print(target_list[target-16],',mae:',num2/len(test_y))
    
    return pred_value,test_y
    

if __name__ == '__main__':


    train_path = "C:/Users/HD/Desktop/code/dataset/1/split12_train_del.csv"
    test_path = "C:/Users/HD/Desktop/code/dataset/1/split12_train_del.csv"


    params = {'num_rounds':350,'max_depth':50,'eta':0.03}

    result_list = {'cod':[],'ss':[],'nh3':[],'tn':[],'tp':[]}
    target_list = ['cod','ss','nh3','tn','tp']
    
    begin = 1
    end = 14

    for target in (19,20):
        df=pd.read_csv(train_path)
        pred = []
        test = []
        for i in range (4000, 6000,12):   
            train_x= df.values[:i,begin:end]
            train_y= df.values[:i,target]
            test_x = df.values[i:i+12,begin:end]
            test_y = df.values[i:i+12,target]
            test.extend(test_y.tolist())
            pred_value,_ = train(train_x,train_y,test_x,test_y,params)
            pred.extend(pred_value.tolist())
        result = {"pred":pred,"true":test}
        df = pd.DataFrame(result)
        df.to_csv('C:/Users/HD/Desktop/CODE/增量测试' + target_list[target-16]+'.csv')

