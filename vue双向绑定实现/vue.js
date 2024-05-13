class Vue{
    constructor(obj_instance){
        this.$data =obj_instance.data;
        Observer(this.$data);
        Compile(obj_instance.el,this)
    }

}

function Observer(data_instance){
    //递归出口
    if(!data_instance||typeof data_instance!=="object") return;
    const dependency =new Dependency()
    Object.keys(data_instance).forEach(key=>{
        let value =data_instance[key];
        Observer(value)
        Object.defineProperty(data_instance,key,{
            enumerable:true,
            configurable:true,
            get(){
                console.log(`访问了属性${key}->${value}`);
                Dependency.temp && dependency.addSub(Dependency.temp);
                // if(Dependency.temp){
                //     console.log(Dependency.temp);
                // }

                return value
            },
            set(newValue){
                // console.log(`属性${key}的值${value}修改为->${newValue}`);
                value=newValue;
                //劫持新的值
                Observer(newValue);
                dependency.notify();
            }
        })
    })
}

//解析模块
function Compile(element,vm){
    vm.$el=document.querySelector(element);
    const fragment = document.createDocumentFragment();
    let child;
    while(child=vm.$el.firstChild){
        fragment.append(child);
    }
    fragment_compile(fragment);
    // console.log(fragment);
    // console.log(fragment.childNodes);

    //替换文档碎片内容
    function fragment_compile(node){
        //正则匹配
        const pattern = /\{\{\s*(\S+)\s*\}\}/;
        if(node.nodeType===3){
            // console.log(node);
            // console.log(node.nodeValue);
            //暂存
            const xxx= node.nodeValue;
            const result_regex=pattern.exec(node.nodeValue);
            if(result_regex){
                // console.log(node.nodeValue);
                // console.log(result_regex[1]);
                const arr = result_regex[1].split(".");
                const value = arr.reduce(
                    (total,current) => total[current],vm.$data
                );
                // console.log(value);
                node.nodeValue=node.nodeValue.replace(pattern,value)
                // console.log(node.nodeValue);
                new Watcher(vm,result_regex[1],(newValue)=>{
                    node.nodeValue=xxx.replace(pattern,newValue);
                })
            }
            return
        }

        if(node.nodeType===1 && node.nodeName==="INPUT"){
            const attr = Array.from(node.attributes);
            attr.forEach(i=>{
                if(i.nodeName==="v-model"){
                    const value = i.nodeValue.split(".").reduce(
                        (total,current) => total[current],vm.$data
                    );
                    node.value=value;
                    console.log(i.nodeValue)
                    new Watcher(vm,i.nodeValue,newValue=>{
                        node.value =newValue;
                    });
                    // console.log(node);
                    node.addEventListener("input",e=>{
                        const arr1 = i.nodeValue.split(".");
                        console.log(arr1);
                        const arr2 = arr1.slice(0,arr1.length-1);
                        console.log(arr2);
                        const final = arr2.reduce(
                            (total,current)=>total[current],vm.$data
                        )
                        // console.log(final);
                        // console.log(value);
                        final[arr1[arr1.length-1]]=e.target.value;
                    });
                }
            })
            // console.log(attr);
        }

        node.childNodes.forEach(child=>fragment_compile(child));
    }
    vm.$el.appendChild(fragment);
}


//依赖-收集和通知订阅者
class Dependency{
    constructor(){
        this.subscribers=[];
    }
    addSub(sub){
        this.subscribers.push(sub);
    }
    notify(){
        this.subscribers.forEach(sub=>sub.updata());
    }
}

//订阅者
class Watcher{  
    constructor(vm,key,callback){
        this.vm=vm;
        this.key=key;
        this.callback=callback;
        Dependency.temp=this;
        // console.log(`用属性${key}创建订阅者`);
        key.split(".").reduce(
            (total,current) => total[current],vm.$data
        );
        Dependency.temp=null;
    }

    updata(){
        const value = this.key.split(".").reduce(
            (total,current) => total[current],vm.$data
        );
        this.callback(value);
    }
}