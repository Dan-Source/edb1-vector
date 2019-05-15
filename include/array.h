
/*
 * TAD: Container Sequencial (aka sequencia, lista)
 *
 * OPERAÇÕES DESEJÁVEIS
 * 0) Criar uma lista de qualquer tipo.
 * 1) Inserir um elemento em uma posição qualquer.
 *    1.1) Inserir uma sequência de elementos em uma posição específica.
 * X) Remover um elemento em uma posição qualquer.
 *    2.1) Remover um sequência de elementos da lista, indicados por um range.
 * 3) Sobrescrever/Alterar um elemento em uma posição específica.
 * 4) Recuperar o tamanho do container.
 * 5) Recuperar o 1ro e último elemento
 * 6) Preencher a lista/container com um valor específico.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib> // size_t
#include <iostream> // std::cerr
#include <exception>
#include <algorithm> // std::min
#include <initializer_list> // std::initializer_list

namespace sc {

    template< typename T, size_t SIZE >
    class array {
        public:
            typedef T& reference;
            typedef size_t size_type;
            typedef T* pointer;

      //=== private area
      private:
          T data[SIZE]; //!< Area de armazenamento dos dados.

          //=== Public interface
      public:

          //=== Special members
          // Contrutor default
          array()
          {/* empty */}
          ~array()
          { /*empty */}

          array& operator=( const array& rhs )
          {
              // Copiar os elementos do clone.
              for( auto i(0u) ; i < SIZE ; i++ )
                  data[i] = rhs.data[i];
              // Copiar os dados do rhs para o objeto que invocou a ação.
              //std::copy ( data, &data[SIZE], rhs.data );

              return *this;
          }

          // Construtor cópia.
          array( const array& clone )
          {
              // Copiar os elementos do clone.
              for( auto i(0u) ; i < SIZE ; i++ )
                  data[i] = clone.data[i];
          }

          // Controi um objeto a partir de uma lista de dados.
          array( std::initializer_list<T> ilist )
          {
              // determinar o menor tamanho para garantir que
              // não vamos gerar segfault.
              auto limit = std::min( ilist.size(), SIZE );

              // Copiar os elementos do clone.
              for( auto i(0u) ; i < limit ; i++ )
                  data[i] = *(ilist.begin()+i);
              //std::copy ( data, data+limit, ilist );
          }


            //=== Interface pública

          /// Recupera/consulta um elemento na posição `pos`, sem verificar os limites da lista.
          T operator[]( size_t pos ) const
          {
              return data[ pos ];
          }

          reference operator[]( size_type pos )
          {
              return data[ pos ];
          }


          /// Insere um elemento `value` na posição `pos`, sem verificar os limites da lista.
          void insert( size_t pos, const T &value )
          {
              data[ pos ] = value;
          }

          /// Insere um elemento `value` na posição `pos`, verificando os limites da lista.
          /*!
           * @throw Gera excecao...
           */
          void at( size_t pos, const T& value )
          {
              if ( pos >= SIZE )
                  throw std::invalid_argument( "[array::at()] Posicao informada alem dos limites do array." );

              data[ pos ] = value;
          }

          /// Retorna o tamanho do array (numero de elementos).
          size_t size() const 
          {
              return SIZE;
          }

          /// Preenche **todo** o array com o valor especificado.
          void fill( const T& value )
          {
              // Percorrer e preencher.
              for( T& e : data )
                  e = value;
          }

          /// Recupera o valor do array na posicao especificada.
          /*! Utilizada do lado esquerdo de uma atribuicao.
           * x = array.at( pos );
           */
          T at( size_t pos ) const
          {
              if ( pos >= SIZE )
                  throw std::invalid_argument( "[array::at() const] Posicao informada alem dos limites do array." );

              return data[ pos ];
          }

          T& at( size_t pos )
          {
              if ( pos >= SIZE )
                  throw std::invalid_argument( "[array::at() const] Posicao informada alem dos limites do array." );

              return data[ pos ];
          }

        }; // class array.

    template < typename T, size_t SIZE >
    std::ostream& operator<<( std::ostream& os, const array<T,SIZE>& A )
    {
        os << "[ ";
        for( auto i(0u) ; i < SIZE ; i++ )
            os << A[i] << " ";
        os << "]";

        return os;
    }

}

#endif
