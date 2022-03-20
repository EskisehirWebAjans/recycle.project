const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  publicPath: process.env.NODE_ENV === 'production'
        ? 'http://185.179.26.181/~recycleproject/'
        : '/'
})
