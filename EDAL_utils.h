/****************************************************************************
*  Copyright 2026 ZJY <Email:zhujinyuan818@gmail.com>                       *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

#ifndef __EDAL_UTILS_H__
#define __EDAL_UTILS_H__

/*============================ INCLUDES ======================================*/

#ifdef   __cplusplus
extern "C" {
#endif


#define __EDAL_CONNECT2(__A, __B)               __A##__B
#define __EDAL_CONNECT3(__A, __B, __C)          __A##__B##__C
#define __EDAL_CONNECT4(__A, __B, __C, __D)     __A##__B##__C##__D

#define EDAL_CONNECT2(__A, __B)                 __EDAL_CONNECT2(__A, __B)
#define EDAL_CONNECT3(__A, __B, __C)            __EDAL_CONNECT3(__A, __B, __C)
#define EDAL_CONNECT4(__A, __B, __C, __D)       __EDAL_CONNECT4(__A,  __B, __C, __D)

/*!
 * \note do NOT use this macro directly
 */
#define __EDAL_VA_NUM_ARGS_IMPL( _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,     \
                                _13,_14,_15,_16,__N,...)      __N

/*!
 * \brief A macro to count the number of parameters
 * 
 * \note if GNU extension is not supported or enabled, the following express will
 *       be false:  (__EDAL_VA_NUM_ARGS() != 0)
 *       This might cause problems when in this library.
 */
#define __EDAL_VA_NUM_ARGS(...)                                                 \
            __EDAL_VA_NUM_ARGS_IMPL( 0,##__VA_ARGS__,16,15,14,13,12,11,10,9,    \
                                      8,7,6,5,4,3,2,1,0)


#ifndef EDAL_SAFE_NAME
#   define EDAL_SAFE_NAME(__NAME)            EDAL_CONNECT3(__, __LINE__, __NAME)
#endif

/*!
 * \brief A macro to safely invode a function pointer
 * 
 * \param[in] __FUNC_PTR the target function pointer
 * \param[in] ... an optional parameter list
 */
#define EDAL_INVOKE(__FUNC_PTR, ...)                                            \
	((NULL == (__FUNC_PTR)) ? 0 : ((*(__FUNC_PTR))(__VA_ARGS__)))

/*!
 * \brief A macro to safely call a function pointer that has no return value
 * 
 * \param[in] __FUNC_PTR the target function pointer
 * \param[in] ... an optional parameter list
 */
#define EDAL_INVOKE_RT_VOID(__FUNC_PTR, ...)                                    \
	if (NULL != (__FUNC_PTR)) (*(__FUNC_PTR))(__VA_ARGS__)


/*!
 * \note do NOT use this macro directly
 */
#define __EDAL_USING1(__declare)                                                \
            for (__declare, *EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr) = NULL;\
                 EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr)++ == NULL;         \
                )

/*!
 * \note do NOT use this macro directly
 */
#define __EDAL_USING2(__declare, __on_leave_expr)                               \
            for (__declare, *EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr) = NULL;\
                 EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr)++ == NULL;         \
                 (__on_leave_expr)                                              \
                )

/*!
 * \note do NOT use this macro directly
 */
#define __EDAL_USING3(__declare, __on_enter_expr, __on_leave_expr)              \
            for (__declare, *EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr) = NULL;\
                 EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr)++ == NULL ?        \
                    ((__on_enter_expr),1) : 0;                                  \
                 (__on_leave_expr)                                              \
                )

/*!
 * \note do NOT use this macro directly
 */
#define __EDAL_USING4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)             \
            for (__dcl1,__dcl2,*EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr)= NULL;  \
                 EDAL_CONNECT3(__EDAL_USING_, __LINE__,_ptr)++ == NULL ?            \
                    ((__on_enter_expr),1) : 0;                                      \
                 (__on_leave_expr)                                                  \
                )

/*!
 * \brief create a code segment with up to two local variables and 
 *        entering/leaving operations
 * \note prototype 1
 *       gui_lv_using(local variable declaration) {
 *           code body 
 *       }
 * 
 * \note prototype 2
 *       gui_lv_using(local variable declaration, {code segment before leaving the body}) {
 *           code body
 *       }
 *
 * \note prototype 3
 *       gui_lv_using( local variable declaration, 
 *                    {code segment before entering the body},
 *                    {code segment before leaving the body}
 *                    ) {
 *           code body 
 *       }
 *
 * \note prototype 4
 *       gui_lv_using( local variable1 declaration,
                       local variable2 with the same type as the local variable 1,
 *                    {code segment before entering the body},
 *                    {code segment before leaving the body}
 *                    ) {
 *           code body 
 *       }
 */
#define gui_lv_using(...)                                                      \
            EDAL_CONNECT2(__EDAL_USING, __EDAL_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


/*!
 * \brief access each items in a given array
 * \param __array the target array
 * \note you can use "_" as the current object (iterator)
 */
#define EDAL_FOREACH1(__array)                                                      \
            gui_lv_using(typeof(__array[0]) *_ = __array)                           \
            for (   uint_fast32_t EDAL_CONNECT2(count,__LINE__) = dimof(__array);   \
                    EDAL_CONNECT2(count,__LINE__) > 0;                              \
                    _++, EDAL_CONNECT2(count,__LINE__)--                            \
                )

/*!
 * \brief access each items in a given array
 * \param __type the type of the array
 * \param __array the target array
 * \note you can use "_" as the current object (iterator)
 */
#define EDAL_FOREACH2(__type, __array)                                              \
            gui_lv_using(__type *_ = __array)                                       \
            for (   uint_fast32_t EDAL_CONNECT2(count,__LINE__) = dimof(__array);   \
                    EDAL_CONNECT2(count,__LINE__) > 0;                              \
                    _++, EDAL_CONNECT2(count,__LINE__)--                            \
                )

/*!
 * \brief access each items in a given array
 * \param __type the type of the array
 * \param __array the target array
 * \param __item a name for the current item (iterator)
 * \note __item is a pointer to the current element
 */
#define EDAL_FOREACH3(__type, __array, __item)                                  \
			EDAL_FOREACH4(__type, __array, dimof(__array), __item)

/*!
 * \brief access each items in a given array
 * \param __type the type of the array
 * \param __array the target array or the pointer of an memory block
 * \param __count number of items in the array/memory block
 * \param __item a name for the current item (iterator)
 * \note __item is a pointer to the current element; for pointer arrays,
 *       use one more dereference to access the stored pointer
 */
#define EDAL_FOREACH4(__type, __array, __count, __item)                         \
			gui_lv_using(                                                       \
				uint_fast32_t EDAL_CONNECT2(count,__LINE__) = (__count)         \
			)                                                                   \
			gui_lv_using(__type *(__item) = NULL)                               \
			for (   __type *_ = (__array);                                      \
					EDAL_CONNECT2(count,__LINE__) > 0;                          \
					_++, (__item) = NULL, EDAL_CONNECT2(count,__LINE__)--       \
				)                                                               \
				if (((__item) = _), 1)

/*!
 * \brief access each items in a given array
 * \note there are 4 prototypes, please refer to EDAL_FOREACH1/2/3/4 for details
 */
#define gui_lv_foreach(...)                                                    \
            EDAL_CONNECT2(EDAL_FOREACH, __EDAL_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)






/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_UTILS_H__ */
