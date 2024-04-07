import { createRequire } from 'module'
const require = createRequire(import.meta.url)
const lib = require('./build/Release/webtransport.node')
lib.initLib()