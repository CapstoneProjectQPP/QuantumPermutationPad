pipeline {
  agent any
  stages {
    stage('Build') {
      agent any
      steps {
        sh 'pwd'
        dir('C++') {
          sh 'pwd'
          sh 'make'
        }
      }
    }
  }
  post {
          // Clean after build
          always {
              cleanWs(cleanWhenNotBuilt: false,
                      deleteDirs: true,
                      disableDeferredWipeout: true,
                      notFailBuild: true,
                      patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                                 [pattern: '.propsfile', type: 'EXCLUDE']])
          }
      }
}