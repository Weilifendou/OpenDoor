// components/touchbar/touchbar.js
Component({
  behaviors:[],
  properties: {
    progress:{
      type: Number,
      value: 0.2
    },
    width: {
      type: Number,
      value: 200
    },
    height: {
      type: Number,
      value: 80
    },
    padding: {
      type: Number,
      value: 3
    },
    radius: {
      type: Number,
      value: 10
    },
    maskColor: {
      type: String,
      value: '#ffffff'
    },
    backColor: {
      type: String,
      value: '#bbbbbb'
    },
    fillColor: {
      type: String,
      value: '#00cccc'
    }
  },
  data: {},
  lifetimes: {
    attached: function() {
      const query = this.createSelectorQuery() //这里居然需要用this去创建，疯了吧
      query.select('#myCanvas')
      .fields({ node: true, size: true })
      .exec((res) => {
        const canvas = res[0].node
        const ctx = canvas.getContext('2d')
        const dpr = wx.getSystemInfoSync().pixelRatio
        canvas.width = res[0].width * dpr
        canvas.height = res[0].height * dpr
        ctx.scale(dpr, dpr)
        this.ctx = ctx
        this.drawProgress(this.properties.progress)
      })
    },
  }, 
  methods: {
    drawProgress: function(progress) {
      let ctx = this.ctx
      let radius = this.properties.radius
      let padding = this.properties.padding
      let width = this.properties.width
      let height = this.properties.height
      let maskColor = this.properties.maskColor
      let backColor = this.properties.backColor
      let fillColor = this.properties.fillColor
      let totalFill = width - padding * 2
      let progressFill = progress * totalFill
      this.totalFill = totalFill
      ctx.fillStyle = backColor
      ctx.fillRect(0, 0, width, height)
      ctx.fillStyle = fillColor
      ctx.fillRect(padding, 0, progressFill, height)
      ctx.beginPath()
      ctx.moveTo(0, 0)
      ctx.lineTo(0, height)
      ctx.lineTo(width, height)
      ctx.lineTo(width, 0)
      ctx.lineTo(0, 0)
      ctx.moveTo(width-padding, height-radius-padding)
      ctx.arc(width-radius-padding, height-radius-padding, radius, 0, Math.PI*0.5)
      ctx.lineTo(radius+padding, height-padding)
      ctx.arc(radius+padding, height-radius-padding, radius, Math.PI*0.5, Math.PI)
      ctx.lineTo(0+padding, radius+padding)
      ctx.arc(radius+padding, radius+padding, radius, Math.PI, Math.PI*1.5)
      ctx.lineTo(width-radius-padding, 0+padding)
      ctx.arc(width-radius-padding, radius+padding, radius, Math.PI*1.5, 0)
      ctx.closePath()
      ctx.fillStyle = maskColor
      ctx.fill()
    },
    touchstart: function(e) {
      this.startProgress = this.properties.progress
      this.startX = e.touches[0].clientX
    },
    touchmove: function(e) {
      let currentX = e.touches[0].clientX
      let diff = currentX - this.startX
      let progressFill = this.startProgress * this.totalFill
      let progress = (diff + progressFill) / this.totalFill
      this.drawProgress(progress)
      this.setData({
        progress: progress
      })
      this.triggerEvent('progressChanged', {progress: this.properties.progress})
    },
    touchend: function(){}
  },
  observers: {
    //此处调用drawProgress会出现fillStyle未定义的情况，貌似并不影响运行
    'progress': function(progress){
      this.drawProgress(progress)
    }
  }
})