Page({
  data:{
    a:0
  },
  next:function(){
    this.setData({
      a:this.data.a+1
    })
  },
  return(){
    wx.navigateTo({
      url: '../index/index'
    })
  }
})