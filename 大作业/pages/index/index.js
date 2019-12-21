Page({
  data:{
    a1:'',
    a2:''
  },
  drink(){
    wx.navigateTo({
      url: '../knowledge/knowledge',
    })
  },
  env:function(){
    var that = this;
    wx.request({
      url: 'http://api.heclouds.com/devices/576710876/datapoints?datastream_id=Temperature',
      header: {
        "content-type": "application/json",
        "api-key": "62qI11qsukvgXqVa6vIaTVYAQKc="
      },
      success: function (res) {
        console.log(res)
        that.setData({
          a2: res.data.data.datastreams[0].datapoints[0].value+'度'
        })
      }
    })
  }
})