// index.js
Page({
  data:{
    progress: 0
  },
  onLoad: function(){
    console.log('hello world')
  },
  add: function(e) {
    let progress = this.data.progress
    progress += 0.1
    this.setData({
      progress: progress
    })
  },
  sutract: function(e) {
    let progress = this.data.progress
    progress -= 0.1
    this.setData({
      progress: progress
    })

  },
  progressChanged: function(e) {
    console.log(e.detail)
  }
})
