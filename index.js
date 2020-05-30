
const unicoding = require('./build/Release/unicoding');

console.log('>', unicoding.calculateUTFInfo("黄伟"));
console.log('>', unicoding.calculateUTFInfo("ḱ"));

module.exports = unicoding;
