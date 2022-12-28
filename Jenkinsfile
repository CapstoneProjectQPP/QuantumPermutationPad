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
}